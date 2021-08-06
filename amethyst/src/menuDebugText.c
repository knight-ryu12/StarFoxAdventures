#include "main.h"


void menuDebugTextMaster_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, enableDebugText ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextMaster_select(const MenuItem *self, int amount) {
    enableDebugText = !enableDebugText;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextPlayerCoords_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_PLAYER_COORDS) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextPlayerCoords_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_PLAYER_COORDS;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextCameraCoords_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_CAMERA_COORDS) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextCameraCoords_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_CAMERA_COORDS;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextRestartPoint_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_RESTART_POINT) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextRestartPoint_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_RESTART_POINT;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextMemoryStats_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_MEMORY_INFO) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextMemoryStats_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_MEMORY_INFO;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextInteractObj_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_INTERACT_OBJ_INFO) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextInteractObj_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_INTERACT_OBJ_INFO;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextHeaps_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_HEAP_STATE) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextHeaps_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_HEAP_STATE;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextBits_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_GAMEBIT_LOG) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextBits_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_GAMEBIT_LOG;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextPlayerState_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_PLAYER_STATE) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextPlayerState_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_PLAYER_STATE;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextTricky_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_TRICKY) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextTricky_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_TRICKY;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextPerf_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_PERFORMANCE) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextPerf_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_PERFORMANCE;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextFPS_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_FPS) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextFPS_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_FPS;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextRNG_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_RNG) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextRNG_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_RNG;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextAudioStreams_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_AUDIO_STREAMS) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextAudioStreams_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_AUDIO_STREAMS;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}


void menuDebugTextAudioSFX_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (debugTextFlags & DEBUGTEXT_AUDIO_SFX) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuDebugTextAudioSFX_select(const MenuItem *self, int amount) {
    debugTextFlags ^= DEBUGTEXT_AUDIO_SFX;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
}

Menu menuDebugText = {
    "デバックテキスト", 0,
    genericMenu_run, genericMenu_draw, debugSubMenu_close,
    "マスター: %s",        menuDebugTextMaster_draw,         menuDebugTextMaster_select,
    "プレイヤーの状態: %s",    menuDebugTextPlayerState_draw,  menuDebugTextPlayerState_select,
    "トリッキー: %s",          menuDebugTextTricky_draw,       menuDebugTextTricky_select,
    "プレイヤー座標: %s",   menuDebugTextPlayerCoords_draw, menuDebugTextPlayerCoords_select,
    "カメラ座標: %s",   menuDebugTextCameraCoords_draw, menuDebugTextCameraCoords_select,
    "復活ポイント: %s",   menuDebugTextRestartPoint_draw, menuDebugTextRestartPoint_select,
    "触れたオブジェクト: %s",    menuDebugTextInteractObj_draw,  menuDebugTextInteractObj_select,
    "GameBit変更: %s", menuDebugTextBits_draw,         menuDebugTextBits_select,
    "メモリの状態: %s",    menuDebugTextMemoryStats_draw,  menuDebugTextMemoryStats_select,
    "ヒープの状態: %s",    menuDebugTextHeaps_draw,        menuDebugTextHeaps_select,
    "パフォーマンス: %s",     menuDebugTextPerf_draw,         menuDebugTextPerf_select,
    "FPSメーター: %s",       menuDebugTextFPS_draw,          menuDebugTextFPS_select,
    "RNG: %s",             menuDebugTextRNG_draw,          menuDebugTextRNG_select,
    "オーディオストリーミング: %s",   menuDebugTextAudioStreams_draw, menuDebugTextAudioStreams_select,
    "オーディオ効果音: %s",       menuDebugTextAudioSFX_draw,     menuDebugTextAudioSFX_select,
    NULL,
};
