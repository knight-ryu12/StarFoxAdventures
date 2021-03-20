#include "main.h"

void debugMapSubMenu_close(const Menu *self) {
    //Close function for submenus of the debug map menu
    curMenu = &menuDebugMap;
    audioPlaySound(NULL, MENU_CLOSE_SOUND);
}

void menuDebugMapReload_select(const MenuItem *self, int amount) {
    if(amount) return;
    mapReload();
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMapObjs_select(const MenuItem *self, int amount) {
    if(amount) return;
    curMenu = &menuDebugObjList;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMapWarp_select(const MenuItem *self, int amount) {
    if(amount) return;
    curMenu = &menuDebugWarp;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMapSetRestart_select(const MenuItem *self, int amount) {
    if(amount) return;
    gplayRestartPoint(&pPlayer->pos.pos, pPlayer->pos.rotation.x, curMapLayer, 0);
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMapClearRestart_select(const MenuItem *self, int amount) {
    if(amount) return;
    gplayClearRestartPoint();
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMapGotoRestart_select(const MenuItem *self, int amount) {
    if(amount) return;
    gplayGotoRestartPoint();
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

Menu menuDebugMap = {
    "Map", 0,
    genericMenu_run, genericMenu_draw, debugSubMenu_close,
    "Objects",             genericMenuItem_draw, menuDebugMapObjs_select,
    "Warp",                genericMenuItem_draw, menuDebugMapWarp_select,
    "Reload Map",          genericMenuItem_draw, menuDebugMapReload_select,
    "Set Restart Point",   genericMenuItem_draw, menuDebugMapSetRestart_select,
    "Clear Restart Point", genericMenuItem_draw, menuDebugMapClearRestart_select,
    "Goto Restart Point",  genericMenuItem_draw, menuDebugMapGotoRestart_select,
    NULL,
};
