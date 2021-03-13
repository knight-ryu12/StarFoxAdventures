#include "main.h"

void (*runLoadingScreens_replaced)();
void runLoadingScreens_hook() {
    /** Runs every frame during the loading screens at the start of the game.
     */
    runLoadingScreens_replaced();

    if(initFrameCount < 200) {
        enableDebugText = 1;
        debugPrintfxy(200, 420, "Amethyst Edition v" MOD_VERSION_STR);
    }
    else if(initFrameCount < 400) {
        debugPrintfxy(250, 420, "segment6.net");
    }
    else if(initFrameCount < 600) {
        debugPrintfxy(60, 420, "\t\tThis is a free fan creation.\n"
            "If you paid for this, you've been scammed.");
    }

    //let's show some console info too, for fun.
    debugPrintfxy(30, 30, "CPU: PowerPC Gekko @ %dMHz type %08X\n"
        "RAM: %d / %dK @ %dMHz + %dK ARAM",
        __OSCoreClock / 1000000, consoleType,
        simMemSize / 1024, realMemSize / 1024,
        __OSBusClock / 1000000, aramSize / 1024);
}


void (*startMsg_initDoneHook_replaced)();
void startMsg_initDoneHook() {
    /** Runs after loading screens.
     *  Turns off debug text if Z isn't held.
     *  We have to do this with a separate hook rather than checking for the
     *  initFrameCount because that's not guaranteed to reach any particular
     *  value if the game loads quickly (especially in Dolphin with fast disc
     *  reading enabled).
     */
    startMsg_initDoneHook_replaced();
    if(!(controllerStates[0].button & PAD_TRIGGER_Z)) {
        enableDebugText = 0;
        OSReport("Turning debug text off");
    }
    else OSReport("Leaving debug text on");
}