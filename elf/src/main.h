#include <sfa/sfa.h>

#define MOD_VERSION_MAJOR 2
#define MOD_VERSION_MINOR 0
#define MOD_VERSION_PATCH 0
#define __STR(x) #x
#define _STR(x) __STR(x)
#define MOD_VERSION_STR _STR(MOD_VERSION_MAJOR) "." _STR(MOD_VERSION_MINOR) "." _STR(MOD_VERSION_PATCH)

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define DRAW_SCALED_TEXTURE_FLIP_H 0x01
#define DRAW_SCALED_TEXTURE_FLIP_V 0x02
#define DRAW_SCALED_TEXTURE_SCALE_FACTOR 256
#define DRAW_SCALED_TEXTURE_SCALE_ONE 256
#define HUD_TEXTURE_BOX_CORNER   10
#define HUD_TEXTURE_BOX_SIDE     11
#define HUD_TEXTURE_BOX_INTERIOR 12
#define HUD_TEXTURE_BOX_TOP      13
#define BOX_BORDER_WIDTH 5
#define BOX_BORDER_HEIGHT 5

//debuglog.s
void debugPrintfHook(const char *fmt, ...);

//debugprint.c
void mainLoopDebugPrint();

//drawbox.c
void drawBox(float x, float y, int w, int h, u8 opacity);

//hook.c
uint32_t hookBranch(uint32_t addr, void *target, int isBl);

//menu.c
void runMenu();

//startmsg.c
extern void (*runLoadingScreens_replaced)();
extern void (*startMsg_initDoneHook_replaced)();
void runLoadingScreens_hook();
void startMsg_initDoneHook();
