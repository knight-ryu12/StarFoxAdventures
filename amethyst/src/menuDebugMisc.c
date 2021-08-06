#include "main.h"

void debugMiscSubMenu_close(const Menu *self) {
    //Close function for submenus of the debug misc menu
    curMenu = &menuDebugMisc;
    audioPlaySound(NULL, MENU_CLOSE_SOUND);
}

void menuDebugMiscHexEdit_select(const MenuItem *self, int amount) {
    if(amount) return;
    hexEditPrevMenu = curMenu;
    curMenu = &menuDebugHexEdit;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMiscDie_select(const MenuItem *self, int amount) {
    if(amount) return;
    playerDie(pPlayer);
}

void menuDebugMiscCrash_select(const MenuItem *self, int amount) {
    if(amount) return;
    (*(u32*)0xBAD0) = 0xDEADDEAD;
}

Menu menuDebugMisc = {
    "その他", 0,
    genericMenu_run, genericMenu_draw, debugSubMenu_close,
    "メモリエディット", genericMenuItem_draw, menuDebugMiscHexEdit_select,
    "プレイヤーkill", genericMenuItem_draw, menuDebugMiscDie_select,
    "ゲームをクラッシュする",  genericMenuItem_draw, menuDebugMiscCrash_select,
    NULL,
};
