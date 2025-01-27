/*
 *  LZO1X Compressor from MiniLZO
 *
 *  Copyright (C) 1996-2005 Markus F.X.J. Oberhumer <markus@oberhumer.com>
 *
 *  The full LZO package can be found at:
 *  http://www.oberhumer.com/opensource/lzo/
 *
 *  Changed for kernel use by:
 *  Nitin Gupta <nitingupta910@gmail.com>
 *  Richard Purdie <rpurdie@openedhand.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "lzo.h"
#include "lzodefs.h"

#define likely(x) x
#define unlikely(x) x
#define s8   int8_t
#define s16  int16_t
#define s32  int32_t
#define s64  int64_t
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define __get_unaligned_le(ptr) (__typeof__(*(ptr)))({			\
	sizeof(*(ptr)) == 1 ? *(ptr) :					\
	  (sizeof(*(ptr)) == 2 ? get_unaligned_le16((ptr)) :		\
	     (sizeof(*(ptr)) == 4 ? get_unaligned_le32((ptr)) :		\
		(sizeof(*(ptr)) == 8 ? get_unaligned_le64((ptr)) :	\
		   __bad_unaligned_access_size())));			\
	})

#define __get_unaligned_be(ptr) (__force __typeof__(*(ptr)))({	\
	sizeof(*(ptr)) == 1 ? *(ptr) :					\
	  (sizeof(*(ptr)) == 2 ? get_unaligned_be16((ptr)) :		\
	     (sizeof(*(ptr)) == 4 ? get_unaligned_be32((ptr)) :		\
		(sizeof(*(ptr)) == 8 ? get_unaligned_be64((ptr)) :	\
		   __bad_unaligned_access_size())));			\
	})

#define __put_unaligned_le(val, ptr) ({					\
	void *__gu_p = (ptr);						\
	switch (sizeof(*(ptr))) {					\
	case 1:								\
		*(u8 *)__gu_p = (__force u8)(val);			\
		break;							\
	case 2:								\
		put_unaligned_le16((__force u16)(val), __gu_p);		\
		break;							\
	case 4:								\
		put_unaligned_le32((__force u32)(val), __gu_p);		\
		break;							\
	case 8:								\
		put_unaligned_le64((__force u64)(val), __gu_p);		\
		break;							\
	default:							\
		__bad_unaligned_access_size();				\
		break;							\
	}								\
	(void)0; })

#define __put_unaligned_be(val, ptr) ({					\
	void *__gu_p = (ptr);						\
	switch (sizeof(*(ptr))) {					\
	case 1:								\
		*(u8 *)__gu_p = (__force u8)(val);			\
		break;							\
	case 2:								\
		put_unaligned_be16((__force u16)(val), __gu_p);		\
		break;							\
	case 4:								\
		put_unaligned_be32((__force u32)(val), __gu_p);		\
		break;							\
	case 8:								\
		put_unaligned_be64((__force u64)(val), __gu_p);		\
		break;							\
	default:							\
		__bad_unaligned_access_size();				\
		break;							\
	}								\
	(void)0; })


#ifdef CONFIG_CPU_BIG_ENDIAN

#define get_unaligned_le32(p)	 __swab32(get_unaligned32(p))
#define get_unaligned_le64(p)	 __swab64(get_unaligned64(p))
#define get_unaligned_be32(p)	 get_unaligned32(p)
#define get_unaligned_be64(p)	 get_unaligned64(p)
#define put_unaligned_le32(v, p) put_unaligned32(__swab32(v), (p))
#define put_unaligned_le64(v, p) put_unaligned64(__swab64(v), (p))
#define put_unaligned_be32(v, p) put_unaligned32((v), (p))
#define put_unaligned_be64(v, p) put_unaligned64((v), (p))
#define get_unaligned	__get_unaligned_be
#define put_unaligned	__put_unaligned_be

#else

#define get_unaligned_le32(p)	 get_unaligned32(p)
#define get_unaligned_le64(p)	 get_unaligned64(p)
#define get_unaligned_be32(p)	 __swab32(get_unaligned32(p))
#define get_unaligned_be64(p)	 __swab64(get_unaligned64(p))
#define put_unaligned_le32(v, p) put_unaligned32((v), (p))
#define put_unaligned_le64(v, p) put_unaligned64((v), (p))
#define put_unaligned_be32(v, p) put_unaligned32(__swab32(v), (p))
#define put_unaligned_be64(v, p) put_unaligned64(__swab64(v), (p))
#define get_unaligned	__get_unaligned_le
#define put_unaligned	__put_unaligned_le

#endif

static inline u16 get_unaligned_le16(const void *p)
{
	const u8 *_p = p;
	return _p[0] | _p[1] << 8;
}

static inline u16 get_unaligned_be16(const void *p)
{
	const u8 *_p = p;
	return _p[0] << 8 | _p[1];
}

static inline void put_unaligned_le16(u16 val, void *p)
{
	u8 *_p = p;
	_p[0] = val;
	_p[1] = val >> 8;
}

static inline void put_unaligned_be16(u16 val, void *p)
{
	u8 *_p = p;
	_p[0] = val >> 8;
	_p[1] = val;
}

static inline u32 get_unaligned32(const void *p)
{
    const u8 *_p = p;
	return _p[0] | (_p[1] << 8) | (_p[2] << 16) | (_p[3] << 24);
}

static inline void put_unaligned32(u32 val, void *p)
{
    u8 *_p = p;
    _p[0] = val;
    _p[1] = val >> 8;
    _p[2] = val >> 16;
    _p[3] = val >> 24;
}

static inline u64 get_unaligned64(const void *p)
{
    const u8 *_p = p;
	return _p[0] | (_p[1] << 8) | (_p[2] << 16) | (_p[3] << 24) |
        (_p[4] << 32) | (_p[5] << 40) | (_p[6] << 48) | (_p[7] << 56);
}

static inline void put_unaligned64(u64 val, void *p)
{
    u8 *_p = p;
    _p[0] = val;
    _p[1] = val >> 8;
    _p[2] = val >> 16;
    _p[3] = val >> 24;
    _p[4] = val >> 32;
    _p[5] = val >> 40;
    _p[6] = val >> 48;
    _p[7] = val >> 56;
}

static int __bad_unaligned_access_size() {
    fprintf(stderr, "__bad_unaligned_access_size\r\n");
    exit(1);
    return 0;
}


static size_t
_lzo1x_1_do_compress(const unsigned char *in, size_t in_len,
		unsigned char *out, size_t *out_len, void *wrkmem)
{
	const unsigned char * const in_end = in + in_len;
	const unsigned char * const ip_end = in + in_len - M2_MAX_LEN - 5;
	const unsigned char ** const dict = wrkmem;
	const unsigned char *ip = in, *ii = ip;
	const unsigned char *end, *m, *m_pos;
	size_t m_off, m_len, dindex;
	unsigned char *op = out;

	ip += 4;

	for (;;) {
		dindex = ((size_t)(0x21 * DX3(ip, 5, 5, 6)) >> 5) & D_MASK;
		m_pos = dict[dindex];

		if (m_pos < in)
			goto literal;

		if (ip == m_pos || ((size_t)(ip - m_pos) > M4_MAX_OFFSET))
			goto literal;

		m_off = ip - m_pos;
		if (m_off <= M2_MAX_OFFSET || m_pos[3] == ip[3])
			goto try_match;

		dindex = (dindex & (D_MASK & 0x7ff)) ^ (D_HIGH | 0x1f);
		m_pos = dict[dindex];

		if (m_pos < in)
			goto literal;

		if (ip == m_pos || ((size_t)(ip - m_pos) > M4_MAX_OFFSET))
			goto literal;

		m_off = ip - m_pos;
		if (m_off <= M2_MAX_OFFSET || m_pos[3] == ip[3])
			goto try_match;

		goto literal;

try_match:
		if (get_unaligned((const unsigned short *)m_pos)
				== get_unaligned((const unsigned short *)ip)) {
			if (likely(m_pos[2] == ip[2]))
					goto match;
		}

literal:
		dict[dindex] = ip;
		++ip;
		if (unlikely(ip >= ip_end))
			break;
		continue;

match:
		dict[dindex] = ip;
		if (ip != ii) {
			size_t t = ip - ii;

			if (t <= 3) {
				op[-2] |= t;
			} else if (t <= 18) {
				*op++ = (t - 3);
			} else {
				size_t tt = t - 18;

				*op++ = 0;
				while (tt > 255) {
					tt -= 255;
					*op++ = 0;
				}
				*op++ = tt;
			}
			do {
				*op++ = *ii++;
			} while (--t > 0);
		}

		ip += 3;
		if (m_pos[3] != *ip++ || m_pos[4] != *ip++
				|| m_pos[5] != *ip++ || m_pos[6] != *ip++
				|| m_pos[7] != *ip++ || m_pos[8] != *ip++) {
			--ip;
			m_len = ip - ii;

			if (m_off <= M2_MAX_OFFSET) {
				m_off -= 1;
				*op++ = (((m_len - 1) << 5)
						| ((m_off & 7) << 2));
				*op++ = (m_off >> 3);
			} else if (m_off <= M3_MAX_OFFSET) {
				m_off -= 1;
				*op++ = (M3_MARKER | (m_len - 2));
				goto m3_m4_offset;
			} else {
				m_off -= 0x4000;

				*op++ = (M4_MARKER | ((m_off & 0x4000) >> 11)
						| (m_len - 2));
				goto m3_m4_offset;
			}
		} else {
			end = in_end;
			m = m_pos + M2_MAX_LEN + 1;

			while (ip < end && *m == *ip) {
				m++;
				ip++;
			}
			m_len = ip - ii;

			if (m_off <= M3_MAX_OFFSET) {
				m_off -= 1;
				if (m_len <= 33) {
					*op++ = (M3_MARKER | (m_len - 2));
				} else {
					m_len -= 33;
					*op++ = M3_MARKER | 0;
					goto m3_m4_len;
				}
			} else {
				m_off -= 0x4000;
				if (m_len <= M4_MAX_LEN) {
					*op++ = (M4_MARKER
						| ((m_off & 0x4000) >> 11)
						| (m_len - 2));
				} else {
					m_len -= M4_MAX_LEN;
					*op++ = (M4_MARKER
						| ((m_off & 0x4000) >> 11));
m3_m4_len:
					while (m_len > 255) {
						m_len -= 255;
						*op++ = 0;
					}

					*op++ = (m_len);
				}
			}
m3_m4_offset:
			*op++ = ((m_off & 63) << 2);
			*op++ = (m_off >> 6);
		}

		ii = ip;
		if (unlikely(ip >= ip_end))
			break;
	}

	*out_len = op - out;
	return in_end - ii;
}

int lzo1x_1_compress(const unsigned char *in, size_t in_len, unsigned char *out,
			size_t *out_len, void *wrkmem)
{
	const unsigned char *ii;
	unsigned char *op = out;
	size_t t;

	if (unlikely(in_len <= M2_MAX_LEN + 5)) {
		t = in_len;
	} else {
		t = _lzo1x_1_do_compress(in, in_len, op, out_len, wrkmem);
		op += *out_len;
	}

	if (t > 0) {
		ii = in + in_len - t;

		if (op == out && t <= 238) {
			*op++ = (17 + t);
		} else if (t <= 3) {
			op[-2] |= t;
		} else if (t <= 18) {
			*op++ = (t - 3);
		} else {
			size_t tt = t - 18;

			*op++ = 0;
			while (tt > 255) {
				tt -= 255;
				*op++ = 0;
			}

			*op++ = tt;
		}
		do {
			*op++ = *ii++;
		} while (--t > 0);
	}

	*op++ = M4_MARKER | 1;
	*op++ = 0;
	*op++ = 0;

	*out_len = op - out;
	return LZO_E_OK;
}

int main(int argc, char **argv) {
    if(argv < 3) {
        printf("usage: lzo infile outfile\r\n");
        return 0;
    }
    FILE *inFile  = strcmp(argv[1], "-") ? fopen(argv[1], "rb") : stdin;
    FILE *outFile = strcmp(argv[2], "-") ? fopen(argv[2], "wb") : stdout;
    //but how the hell do you use it?
    return 0;
}
