/** Main in-game menu.
 */
#include "main.h"

void mainMenu_close(const Menu *self) {
    //Close function for main menu
    //DPRINT("Close main menu");
    menuState = MENU_CLOSING;
    menuAnimFrame = MENU_ANIM_NUM_FRAMES;
    if(!(menuPrevGameFlags & MENU_FLAG_TIME_STOPPED)) timeStop = 0;
    if(!(menuPrevGameFlags & MENU_FLAG_PAUSE_DISABLED)) pauseDisabled = 0;
    activeTimerFlags = menuPrevTimerFlags;
    audioPlaySound(NULL, MENU_CLOSE_SOUND);
}

void mainSubMenu_close(const Menu *self) {
    //Close function for submenus of the main menu
    curMenu = &menuMain;
    audioPlaySound(NULL, MENU_CLOSE_SOUND);
}

void menuMainGameSettings_select(const MenuItem *self, int amount) {
    if(amount) return; //no adjustment
    curMenu = &menuGameSettings;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuMainControlSettings_select(const MenuItem *self, int amount) {
    if(amount) return; //no adjustment
    curMenu = &menuControlSettings;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuMainPlayerSettings_select(const MenuItem *self, int amount) {
    if(amount) return; //no adjustment
    curMenu = &menuPlayerSettings;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuMainVideoSettings_select(const MenuItem *self, int amount) {
    if(amount) return; //no adjustment
    curMenu = &menuVideoSettings;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuMainAudioSettings_select(const MenuItem *self, int amount) {
    if(amount) return; //no adjustment
    curMenu = &menuAudioSettings;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuMainPdaSettings_select(const MenuItem *self, int amount) {
    if(amount) return; //no adjustment
    curMenu = &menuPdaSettings;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuMainDebug_select(const MenuItem *self, int amount) {
    if(amount) return; //no adjustment
    curMenu = &menuDebug;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

Menu menuMain = {
    "PDAメニュー", 0,
    genericMenu_run, genericMenu_draw, mainMenu_close,
    "ゲーム設定",    genericMenuItem_draw, menuMainGameSettings_select,
    "コントロール設定", genericMenuItem_draw, menuMainControlSettings_select,
    "プレイヤー設定",  genericMenuItem_draw, menuMainPlayerSettings_select,
    "ビデオ設定",   genericMenuItem_draw, menuMainVideoSettings_select,
    "オーディオ設定",   genericMenuItem_draw, menuMainAudioSettings_select,
    "PDA設定",     genericMenuItem_draw, menuMainPdaSettings_select,
    "デバッグ",            genericMenuItem_draw, menuMainDebug_select,
    NULL,
};
