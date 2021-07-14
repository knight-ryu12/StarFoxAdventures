/** Title screen improvements.
 */
#include "main.h"

static int (*oldTitleHook)();

int titleHook() {
    //check current and previous frame
    u16 buttons = controllerStates[0].button | controllerStates[4].button;

    debugPrintf("saveStatus = %d\n", saveStatus);
    if(saveStatus < 0 && buttons & PAD_TRIGGER_L) {
        titleScreenActive = false;
        titleScreen_panAwayFromMovieTimer = 0;
        saveGame_load(0);
        //interesting: calling this during the game still works, and replaces your current save
        //data, so things like your items are reset, but you don't reload or respawn...
    }

    return oldTitleHook();
}

void titleHooksInit() {
    //hook into the run method of the title screen DLL
    oldTitleHook = *(u32*)0x8031a320;
    WRITE32(0x8031a320, titleHook);
}
