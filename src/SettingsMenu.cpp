#include "PepeDraw.h"
#include "Settings.h"
#include "Pins.h"
#include "NVSStore.h"
#include "WifiConfig.h"
#include "SoundUtils.h"

static int cursor = 0;
static const int MENU_ITEMS = 4;   // antes 3, agora 4 com FORGET WIFI

// ═══════════════════════════════════════════════════════════════════════════
//  ESQUECER REDE WIFI · apaga as credenciais salvas no NVS
// ═══════════════════════════════════════════════════════════════════════════
static void runForgetWifi() {
    // Espera a liberação do OK
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);

    // Caso 1: não há rede salva
    if (!wifiConfigHasSaved()) {
        tft.fillScreen(TFT_BLACK);
        tft.drawRect(0, 0, 320, 240, TFT_WHITE);
        drawStringCustom(30, 10, "WIFI CONFIG", TFT_WHITE, 3);
        tft.drawFastHLine(0, 45, 320, TFT_WHITE);

        drawStringCustom(40, 90, "SEM REDE SALVA", UI_ACCENT, 2);
        drawStringCustom(40, 130, "Nao ha credenciais WiFi", TFT_WHITE, 1);
        drawStringCustom(40, 145, "salvas neste momento.", TFT_WHITE, 1);
        drawStringCustom(10, 222, "OK: Voltar", UI_ACCENT, 1);

        beep(1500, 60);

        while (digitalRead(BTN_OK) == HIGH) delay(20);
        beep(1800, 40);
        while (digitalRead(BTN_OK) == LOW) delay(5);
        delay(100);
        return;
    }

    // Caso 2: há rede salva → confirmar
    String savedSSID = wifiConfigGetSavedSSID();

    tft.fillScreen(TFT_BLACK);
    tft.drawRect(0, 0, 320, 240, TFT_RED);
    tft.drawRect(1, 1, 318, 238, TFT_RED);

    drawStringCustom(40, 12, "ESQUECER WIFI", TFT_RED, 3);
    tft.drawFastHLine(0, 50, 320, TFT_RED);

    drawStringCustom(20, 70, "Rede salva:", TFT_WHITE, 1);

    String ssidDisp = savedSSID;
    if (ssidDisp.length() > 26) ssidDisp = ssidDisp.substring(0, 24) + "..";
    drawStringCustom(20, 90, ssidDisp, UI_SELECT, 2);

    drawStringCustom(20, 130, "Apagar credenciais?", TFT_WHITE, 1);
    drawStringCustom(20, 144, "Na proxima vez que usar uma", UI_ACCENT, 1);
    drawStringCustom(20, 156, "ferramenta com WiFi sera", UI_ACCENT, 1);
    drawStringCustom(20, 168, "preciso escolher a rede.", UI_ACCENT, 1);

    tft.drawFastHLine(0, 210, 320, TFT_RED);
    drawStringCustom(10, 220, "OK: SIM APAGAR  UP/DN: CANCELAR", UI_ACCENT, 1);

    while (true) {
        if (digitalRead(BTN_OK) == LOW) {
            beep(1200, 80);
            while (digitalRead(BTN_OK) == LOW) delay(5);
            delay(100);

            // Apaga as credenciais
            wifiConfigForget();

            // Tela de confirmação
            tft.fillScreen(TFT_BLACK);
            tft.drawRect(0, 0, 320, 240, TFT_WHITE);
            drawStringCustom(40, 90, "REDE ESQUECIDA", TFT_GREEN, 3);
            drawStringCustom(40, 140, "Credenciais apagadas.", TFT_WHITE, 1);

            beep(2400, 50); delay(30);
            beep(3000, 80);
            delay(1500);
            return;
        }
        if (digitalRead(BTN_UP) == LOW || digitalRead(BTN_DOWN) == LOW) {
            beep(2000, 40);
            while (digitalRead(BTN_UP) == LOW || digitalRead(BTN_DOWN) == LOW)
                delay(5);
            delay(100);
            return;
        }
        delay(20);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  MENU SETTINGS PRINCIPAL
// ═══════════════════════════════════════════════════════════════════════════

void drawSettings() {
    tft.fillScreen(TFT_BLACK);

    tft.drawRect(0, 0, 320, 240, TFT_WHITE);
    drawStringCustom(30, 10, "SETTINGS", TFT_WHITE, 3);
    tft.drawFastHLine(0, 45, 320, TFT_WHITE);

    String soundStr = soundEnabled ? "ON" : "OFF";

    for (int i = 0; i < MENU_ITEMS; i++) {
        int y = 60 + (i * 38);

        if (i == cursor) {
            tft.fillRect(10, y - 5, 300, 30, TFT_WHITE);
        }

        uint16_t textColor = (i == cursor) ? TFT_BLACK : TFT_WHITE;

        if (i == 0) {
            drawStringCustom(20, y, "SOUND: " + soundStr, textColor, 2);
        }
        else if (i == 1) {
            drawStringCustom(20, y, "VOLUME: " + String(soundVolume),
                             textColor, 2);
        }
        else if (i == 2) {
            drawStringCustom(20, y, "FORGET WIFI", textColor, 2);
        }
        else if (i == 3) {
            drawStringCustom(20, y, "BACK", textColor, 2);
        }
    }
}

void runSettings() {

    cursor = 0;

    // Evita OK duplo
    while (digitalRead(BTN_OK) == LOW);
    delay(150);

    bool exitMenu = false;

    drawSettings();

    while (!exitMenu) {

        if (digitalRead(BTN_DOWN) == LOW) {
            cursor = (cursor + 1) % MENU_ITEMS;
            drawSettings();
            delay(200);
        }

        if (digitalRead(BTN_UP) == LOW) {
            cursor = (cursor - 1 + MENU_ITEMS) % MENU_ITEMS;
            drawSettings();
            delay(200);
        }

        if (digitalRead(BTN_OK) == LOW) {

            if (cursor == 0) {
                soundEnabled = !soundEnabled;
                nvsSetBool("sound_on", soundEnabled);
            }
            else if (cursor == 1) {
                soundVolume++;
                if (soundVolume > 5) soundVolume = 1;
                nvsSetInt("sound_vol", soundVolume);
            }
            else if (cursor == 2) {
                // Espera a liberação antes de entrar na sub-tela
                while (digitalRead(BTN_OK) == LOW);
                delay(100);
                runForgetWifi();
            }
            else if (cursor == 3) {
                exitMenu = true;
            }

            drawSettings();

            while (digitalRead(BTN_OK) == LOW);
            delay(150);
        }

        delay(10);
    }
}