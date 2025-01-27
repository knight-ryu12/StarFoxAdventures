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

void menuDebugMapSpawnObj_select(const MenuItem *self, int amount) {
    if(amount) return;
    curMenu = &menuDebugSpawnObj;
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

void menuDebugMapSetSavePos_select(const MenuItem *self, int amount) {
    if(amount) return;
    if(!pCurSaveGame) {
        audioPlaySound(NULL, MENU_FAIL_SOUND);
        return;
    }
    //these are the coords you'll actually spawn at when loading the save.
    PlayerCharPos *playerPos =
        //&saveData.curSaveGame.charPos[saveData.curSaveGame.character];
        &pCurSaveGame->charPos[pCurSaveGame->character];
    playerPos->pos.x = pPlayer->pos.pos.x;
    playerPos->pos.y = pPlayer->pos.pos.y;
    playerPos->pos.z = pPlayer->pos.pos.z;
    playerPos->mapLayer = curMapLayer;
    playerPos->mapId = curMapId;
    playerPos->rotX  = pPlayer->pos.rotation.x >> 8;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMapGotoSave_select(const MenuItem *self, int amount) {
    if(amount) return;
    gplayGotoSavegame();
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMapStates_select(const MenuItem *self, int amount) {
    if(amount) return;
    curMenu = &menuDebugMapStates;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

void menuDebugMapEnv_select(const MenuItem *self, int amount) {
    if(amount) return;
    curMenu = &menuDebugMapEnv;
    audioPlaySound(NULL, MENU_OPEN_SOUND);
}

Menu menuDebugMap = {
    "マップ", 0,
    genericMenu_run, genericMenu_draw, debugSubMenu_close,
    "ワープ",                genericMenuItem_draw, menuDebugMapWarp_select,
    "オブジェクト",             genericMenuItem_draw, menuDebugMapObjs_select,
    "オブジェクト召喚",        genericMenuItem_draw, menuDebugMapSpawnObj_select,
    "マップリロード",          genericMenuItem_draw, menuDebugMapReload_select,
    "リスタートポイント設定",   genericMenuItem_draw, menuDebugMapSetRestart_select,
    "リスタートポイント解除", genericMenuItem_draw, menuDebugMapClearRestart_select,
    "リスタートポイントに移動",  genericMenuItem_draw, menuDebugMapGotoRestart_select,
    "セーブポジション設定",       genericMenuItem_draw, menuDebugMapSetSavePos_select,　// Saved means that actually "saved?"
    "最後にセーブした場所に移動",      genericMenuItem_draw, menuDebugMapGotoSave_select,
    "マップの状態",          genericMenuItem_draw, menuDebugMapStates_select,
    "環境",         genericMenuItem_draw, menuDebugMapEnv_select,
    NULL,
};
