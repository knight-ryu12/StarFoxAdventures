# some generic code used by multiple submodules.

intToFloat: # convert r3 from int to float.
    # stores result in f1.
    # clobbers f9, r0, r3, SP_FLOAT_TMP
    lfd     f9, (floatMagic - mainLoop)(r14) # load constant into f9
    lis     r0, 0x4330
    stw     r0, SP_FLOAT_TMP(r1) # store exponent part for integer

    xoris r3, r3, 0x8000         # invert sign of integer
    stw   r3, SP_FLOAT_TMP+4(r1) # store fraction part for integer
    lfd   f1, SP_FLOAT_TMP(r1)   # load integer in double format into f1
    fsub  f1, f1, f9             # f1 contains converted integer
    frsp  f1, f1                 # double to single
    blr

adjItem_float: # r3=adj, r5=&val, f2=adjStep, f3=min, f4=max
    lfs     f1, 0(r5) # f1 = val
    cmpwi   r3, 0
    bge     .noNegFloat
    fneg    f2, f2
.noNegFloat:
    fadds   f1, f1, f2 # f2 = -adjStep
    fcmpo   0, f1, f3 # f1 < min?
    bge     .float_moreThanMin
    # XXX wraparound doesn't work nicely due to rounding error.
    # sometims you'll jump from 10% to 200% instead of to 0%.
    # (fun fact: Super Smash Bros Melee's debug menus have this
    # exact same bug.)
    #fmr     f1, f4 # f1 = max
    fmr     f1, f3 # f1 = min
.float_moreThanMin:
    fcmpo   0, f1, f4 # f1 > max?
    ble     .float_lessThanMax
    #fmr     f1, f3 # f1 = min
    fmr     f1, f4 # f1 = max
.float_lessThanMax:
    stfs    f1, 0(r5)
    blr


menuHideHud:
    li     r3, 1
    LOADWH r4, hudHidden
    STOREB r3, hudHidden, r4
    li     r3, 0
    LOADWH r4, pdaOn
    STOREB r3, pdaOn, r4
    blr