/** Game Settings submenu.
 */
#include "main.h"

void menuGameSpeed_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (int)((physicsTimeScale * 100) / 60));
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuGameSpeed_select(const MenuItem *self, int amount) {
    physicsTimeScale += amount * 15;
    if(physicsTimeScale <  15) physicsTimeScale =  15;
    if(physicsTimeScale > 240) physicsTimeScale = 240;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
    updateSaveData();
}


void menuAutoSave_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, bAutoSave ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuAutoSave_select(const MenuItem *self, int amount) {
    bAutoSave = !bAutoSave;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
    updateSaveData();
}


void menuSubtitles_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, bSubtitlesEnabled ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuSubtitles_select(const MenuItem *self, int amount) {
    bSubtitlesEnabled = !bSubtitlesEnabled;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
    updateSaveData();
}

static const char *languages[NUM_LANGUAGES] = {
    "English", "French", "German", "Italian", "Japanese", "Spanish"
};
void menuLanguage_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, languages[curLanguage]);
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuLanguage_select(const MenuItem *self, int amount) {
    curLanguage += amount;
    if(curLanguage < 0) curLanguage = NUM_LANGUAGES - 1;
    if(curLanguage >= NUM_LANGUAGES) curLanguage = 0;
    GameTextDir32 dir = curGameTextDir;
    gameTextLoadDir(GAMETEXT_DIR_Link); //load HUD texts
    gameTextLoadDir(dir); //then load current map's texts
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
    updateSaveData();
}


void menuHpFlash_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (hudFlags & HUD_LOW_HP_FLASH) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuHpFlash_select(const MenuItem *self, int amount) {
    hudFlags ^= HUD_LOW_HP_FLASH;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
    updateSaveData();
}

void menuHpSound_draw(const MenuItem *self, int x, int y, bool selected) {
    char str[64];
    sprintf(str, self->name, (hudFlags & HUD_LOW_HP_BEEP) ? "On" : "Off");
    gameTextShowStr(str, MENU_TEXTBOX_ID, x, y);
}
void menuHpSound_select(const MenuItem *self, int amount) {
    hudFlags ^= HUD_LOW_HP_BEEP;
    audioPlaySound(NULL, MENU_ADJUST_SOUND);
    updateSaveData();
}

Menu menuGameSettings = {
    "ゲーム設定", 0,
    genericMenu_run, genericMenu_draw, mainSubMenu_close,
    "ゲーム速度: %d%%", menuGameSpeed_draw, menuGameSpeed_select,
    "オートセーブ: %s",     menuAutoSave_draw,  menuAutoSave_select,
    "サブタイトル: %s",    menuSubtitles_draw, menuSubtitles_select,
    "言語: %s",     menuLanguage_draw,  menuLanguage_select,
    "HP低下 フラッシュ: %s", menuHpFlash_draw,   menuHpFlash_select,
    "HP低下 音: %s", menuHpSound_draw,   menuHpSound_select,
    NULL,
};
