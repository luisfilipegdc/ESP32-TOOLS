#include "MenuSystem.h"
#include "PepeDraw.h"
#include "Icons.h"
#include "Pins.h"
#include "SoundUtils.h"

// Handlers das ferramentas existentes (chamadas a partir do carrossel)
#include "WifiScanner.h"
#include "RadioScanner.h"
#include "RadioJammer.h"
#include "PacketMonitor.h"
#include "SettingsMenu.h"
#include "SystemInfo.h"
#include "SystemInfo.h"
#include "BLEScanner.h"
#include "BLESpam.h"
#include "BTDisruptor.h"
#include "BeaconSpam.h"
#include "Deauther.h"
#include "EvilPortal.h"
#include "Screensaver.h"
#include "ProbeSniffer.h"
#include "Karma.h"
#include "ClockWeather.h"
#include "About.h"
#include "AjoloteSprite.h"

// ═══════════════════════════════════════════════════════════════════════════
//  CARROSSEL PRINCIPAL
// ═══════════════════════════════════════════════════════════════════════════

// ── Registro das categorias do menu principal ───────────────────────────
// NOTA: por enquanto cada categoria leva direto a uma ferramenta (compat.
//       com o que já existe). Quando adicionarmos submenus reais, o handler
//       apontará para uma função que chame runSubMenu() com sua lista.
// Submenu WIFI TOOLS · WiFi Scanner + Beacon Spam + Deauther
static void handlerWifi() {
    static const char* wifiItems[] = {
        "WiFi Scanner",
        "Beacon Spam",
        "Deauther",
        "Evil Portal",
        "Probe Sniffer",
        "KARMA Attack"
    };
    static const int wifiCount = sizeof(wifiItems) / sizeof(char*);

    bool exitSub = false;
    while (!exitSub) {
        int choice = runSubMenu("WIFI TOOLS", wifiItems, wifiCount);
        switch (choice) {
            case -1: exitSub = true;     break;
            case  0: runWifiScan();      break;
            case  1: runBeaconSpam();    break;
            case  2: runDeauther();      break;
            case  3: runEvilPortal();    break;
            case  4: runProbeSniffer();  break;
            case  5: runKarma();         break;
        }
    }
}

// Submenu BLUETOOTH · BLE Scanner + BLE Spam
// Submenu BLUETOOTH · BLE Scanner + BLE Spam + BT Disruptor
static void handlerBT() {
    static const char* btItems[] = {
        "BLE Scanner",
        "BLE Spam",
        "BT Disruptor"
    };
    static const int btCount = sizeof(btItems) / sizeof(char*);

    bool exitSub = false;
    while (!exitSub) {
        int choice = runSubMenu("BLUETOOTH", btItems, btCount);
        switch (choice) {
            case -1: exitSub = true;     break;
            case  0: runBLEScanner();    break;
            case  1: runBLESpam();       break;
            case  2: runBTDisruptor();   break;
        }
    }
}

static void handlerMonitor() { runPacketMonitor(); }

// Submenu RADIO TOOLS · abre a lista com Jammer + Spectrum
static void handlerRadio() {
    static const char* radioItems[] = {
        "Jammer",
        "Spectrum"
    };
    static const int radioCount = sizeof(radioItems) / sizeof(char*);

    bool exitSub = false;
    while (!exitSub) {
        int choice = runSubMenu("RADIO TOOLS", radioItems, radioCount);
        switch (choice) {
            case -1: exitSub = true;        break;   // < BACK
            case  0: runRadioJammer();      break;
            case  1: runRadioScanner();     break;
        }
    }
}

// Submenu SYSTEM · abre a lista com Settings + System Info
static void handlerSystem() {
    static const char* systemItems[] = {
        "Settings",
        "System Info",
        "Clock & Weather",
        "About"
    };
    static const int systemCount = sizeof(systemItems) / sizeof(char*);

    bool exitSub = false;
    while (!exitSub) {
        int choice = runSubMenu("SYSTEM", systemItems, systemCount);
        switch (choice) {
            case -1: exitSub = true;       break;
            case  0: runSettings();        break;
            case  1: runSystemInfo();      break;
            case  2: runClockWeather();    break;
            case  3: runAbout();           break;
        }
    }
}

// Nota: RadioScanner (o espectrômetro) foi movido para "RADIO TOOLS" quando
//       tivermos submenus reais. Por ora acessível pelo menu SYSTEM
//       ou podemos deixá-lo como categoria própria provisória.

static const MainMenuEntry MAIN_ENTRIES[] = {
    { "WIFI TOOLS",      "Scan, Deauth, ...",   ICON_WIFI,      handlerWifi    },
    { "RADIO TOOLS",     "Jammer, Scanner",     ICON_RADIO,     handlerRadio   },
    { "BLUETOOTH",       "BLE Scan, Spam",      ICON_BLUETOOTH, handlerBT      },
    { "MONITOR",         "Packet sniffer",      ICON_MONITOR,   handlerMonitor },
    { "SYSTEM",          "Settings, Info",      ICON_SYSTEM,    handlerSystem  },
};
static const int MAIN_COUNT = sizeof(MAIN_ENTRIES) / sizeof(MainMenuEntry);

static int currentEntry = 0;

// ═══════════════════════════════════════════════════════════════════════════
//  HELPERS DE DESENHO
// ═══════════════════════════════════════════════════════════════════════════

// Desenha o header com contador "< X/N >" à direita
static void drawMainHeader() {
    tft.fillRect(1, 1, 318, 28, TFT_BLACK);
    drawStringBig(10, 8, "ESP32-TOOLS", UI_MAIN, 1);

    String counter = "< " + String(currentEntry + 1) + "/" +
                     String(MAIN_COUNT) + " >";
    int w = getTextWidth(counter, 1);
    drawStringCustom(315 - w, 12, counter, UI_ACCENT, 1);

    tft.drawFastHLine(0, 30, 320, UI_ACCENT);
}

// Desenha o footer com as dicas de botões
static void drawMainFooter() {
    tft.drawFastHLine(0, 215, 320, UI_ACCENT);
    tft.fillRect(1, 217, 318, 22, TFT_BLACK);
    drawStringCustom(10, 223, "UP/DN: NAVEGAR", UI_ACCENT, 1);
    drawStringCustom(230, 223, "OK: ENTRAR", UI_ACCENT, 1);
}

// Desenha o ícone + texto do card centralizado na tela.
// `yOffset` permite deslocar verticalmente para a animação de slide.
// `highlighted` = true quando o usuário acabou de apertar OK (flash laranja)
static void drawCard(int entryIdx, int yOffset, bool highlighted) {
    if (entryIdx < 0 || entryIdx >= MAIN_COUNT) return;

    const MainMenuEntry& e = MAIN_ENTRIES[entryIdx];
    uint16_t iconColor  = highlighted ? UI_SELECT : UI_MAIN;
    uint16_t titleColor = highlighted ? UI_SELECT : UI_MAIN;

    // Ícone centralizado horizontalmente, um pouco acima do centro vertical
    int iconCx = 160;
    int iconCy = 95 + yOffset;
    // Clipping na área central (entre header y=30 e footer y=215)
    drawIcon(iconCx, iconCy, e.icon, iconColor, 31, 214);

    // Título abaixo do ícone com fonte BIG
    int titleY = 150 + yOffset;
    String title = e.title;
    int tw = getTextWidth(title, 2, FONT_BIG);
    drawStringBig((320 - tw) / 2, titleY, title, titleColor, 2);

    // Subtítulo com fonte SMALL
    int subY = 180 + yOffset;
    String sub = e.subtitle;
    int sw = getTextWidth(sub, 1);
    drawStringCustom((320 - sw) / 2, subY, sub, UI_ACCENT, 1);
}

// Limpa apenas a área interna (entre header e footer) para redesenhar
static void clearCardArea() {
    tft.fillRect(1, 31, 318, 183, TFT_BLACK);
}

// ═══════════════════════════════════════════════════════════════════════════
//  ANIMAÇÃO DE SLIDE
//  O card atual sai em uma direção, o novo entra pela direção oposta.
//  direction = +1 → o novo entra por baixo (navegamos DOWN)
//  direction = -1 → o novo entra por cima (navegamos UP)
// ═══════════════════════════════════════════════════════════════════════════
static void slideAnimation(int oldIdx, int newIdx, int direction) {
    const int STEPS   = 6;
    const int TRAVEL  = 120;

    for (int step = 1; step <= STEPS; step++) {
        int offset = (TRAVEL * step) / STEPS;
        int oldOff = -direction * offset;
        int newOff =  direction * (TRAVEL - offset);

        clearCardArea();
        drawCard(oldIdx, oldOff, false);
        drawCard(newIdx, newOff, false);

        // Cobre qualquer pixel que tenha vazado para o footer
        tft.fillRect(1, 215, 318, 24, TFT_BLACK);
        tft.drawFastHLine(0, 215, 320, UI_ACCENT);
        drawStringCustom(10, 223, "UP/DN: NAVEGAR", UI_ACCENT, 1);
        drawStringCustom(230, 223, "OK: ENTRAR", UI_ACCENT, 1);

        delay(12);
    }

    clearCardArea();
    drawCard(newIdx, 0, false);
}

// ═══════════════════════════════════════════════════════════════════════════
//  MAIN MENU · carrossel vertical
// ═══════════════════════════════════════════════════════════════════════════
void runMainMenu() {
    // Desenha a moldura completa inicial
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(0, 0, 320, 240, UI_MAIN);
    drawMainHeader();
    drawMainFooter();
    drawCard(currentEntry, 0, false);

    unsigned long lastPress = 0;
    unsigned long lastActivity = millis();   // ← NOVO: rastreio de inatividade

    while (true) {

        // ── UP: card anterior (wrap-around) ────────────────────────────
        if (digitalRead(BTN_UP) == LOW && (millis() - lastPress > 200)) {
            int prev = (currentEntry - 1 + MAIN_COUNT) % MAIN_COUNT;
            beep(2200, 25);
            slideAnimation(currentEntry, prev, -1);
            currentEntry = prev;
            drawMainHeader();
            lastPress = millis();
            lastActivity = millis();              // ← NOVO
        }

        // ── DOWN: próximo card (wrap-around) ────────────────────────────
        if (digitalRead(BTN_DOWN) == LOW && (millis() - lastPress > 200)) {
            int next = (currentEntry + 1) % MAIN_COUNT;
            beep(2200, 25);
            slideAnimation(currentEntry, next, +1);
            currentEntry = next;
            drawMainHeader();
            lastPress = millis();
            lastActivity = millis();              // ← NOVO
        }

        // ── OK: flash laranja + chamar o handler ───────────────────────
        if (digitalRead(BTN_OK) == LOW && (millis() - lastPress > 350)) {
            // Flash de seleção: 3 pulsos rápidos de cor
            for (int i = 0; i < 3; i++) {
                clearCardArea();
                drawCard(currentEntry, 0, true);
                beep(1500 + i * 300, 40);
                delay(60);
                clearCardArea();
                drawCard(currentEntry, 0, false);
                delay(40);
            }

            // Executa a ferramenta
            MAIN_ENTRIES[currentEntry].handler();

            // Ao retornar, redesenha o menu inteiro
            tft.fillScreen(TFT_BLACK);
            tft.drawRect(0, 0, 320, 240, UI_MAIN);
            drawMainHeader();
            drawMainFooter();
            drawCard(currentEntry, 0, false);
            lastPress = millis();
            lastActivity = millis();              // ← NOVO
        }

        // ── SCREENSAVER: se houver 30s sem atividade, disparar ─────────
        if (millis() - lastActivity > SCREENSAVER_IDLE_MS) {
            runScreensaver();   // bloqueia até o usuário pressionar um botão

            // Ao retornar, redesenha o menu inteiro
            tft.fillScreen(TFT_BLACK);
            tft.drawRect(0, 0, 320, 240, UI_MAIN);
            drawMainHeader();
            drawMainFooter();
            drawCard(currentEntry, 0, false);
            lastActivity = millis();              // reseta a inatividade
            lastPress = millis();
        }

        delay(10);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  SUB MENU · lista vertical rolável com BACK no início
//  · Retorna o índice 0..count-1 do item escolhido
//  · Retorna -1 se o usuário escolheu "< BACK" ou segurou o OK
// ═══════════════════════════════════════════════════════════════════════════
int runSubMenu(const char* title, const char* items[], int count) {
    const int VISIBLE       = 5;
    const int LINE_HEIGHT   = 30;
    const int LIST_Y_START  = 50;

    int totalItems   = count + 1;   // +1 pelo BACK
    int cursor       = 0;
    int scrollOffset = 0;
    bool needsRedraw = true;
    int result       = -2;

    unsigned long lastPress = 0;

    // Espera soltar o OK do menu anterior
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);

    while (result == -2) {

        if (needsRedraw) {
            tft.fillScreen(TFT_BLACK);
            tft.drawRect(0, 0, 320, 240, UI_MAIN);

            // Header
            tft.fillRect(1, 1, 318, 28, TFT_BLACK);
            drawStringBig(10, 8, title, UI_MAIN, 1);
            tft.drawFastHLine(0, 30, 320, UI_ACCENT);

            // Items
            for (int i = 0; i < VISIBLE; i++) {
                int idx = i + scrollOffset;
                if (idx >= totalItems) break;

                int y = LIST_Y_START + i * LINE_HEIGHT;
                bool selected = (idx == cursor);

                if (selected) {
                    tft.fillRect(8, y - 4, 304, LINE_HEIGHT - 4, UI_SELECT);
                }

                uint16_t textColor = selected ? UI_BG : UI_MAIN;

                if (idx == 0) {
                    drawStringCustom(20, y + 2, "< BACK", textColor, 2);
                } else {
                    drawStringCustom(20, y + 2, items[idx - 1], textColor, 2);
                }
            }

            // Barra de rolagem lateral
            if (totalItems > VISIBLE) {
                int barH = (VISIBLE * 170) / totalItems;
                int barY = 40 + (scrollOffset * (170 - barH)) / (totalItems - VISIBLE);
                tft.fillRect(313, barY, 4, barH, UI_ACCENT);
            }

            // Footer
            tft.drawFastHLine(0, 215, 320, UI_ACCENT);
            drawStringCustom(10, 223, "UP/DN: NAVEGAR   OK: SELEC",
                             UI_ACCENT, 1);

            needsRedraw = false;
        }

        // UP
        if (digitalRead(BTN_UP) == LOW && (millis() - lastPress > 180)) {
            cursor = (cursor - 1 + totalItems) % totalItems;
            if (cursor < scrollOffset) scrollOffset = cursor;
            if (cursor >= scrollOffset + VISIBLE)
                scrollOffset = cursor - VISIBLE + 1;
            beep(2200, 25);
            needsRedraw = true;
            lastPress = millis();
        }

        // DOWN
        if (digitalRead(BTN_DOWN) == LOW && (millis() - lastPress > 180)) {
            cursor = (cursor + 1) % totalItems;
            if (cursor < scrollOffset) scrollOffset = cursor;
            if (cursor >= scrollOffset + VISIBLE)
                scrollOffset = cursor - VISIBLE + 1;
            beep(2200, 25);
            needsRedraw = true;
            lastPress = millis();
        }

        // OK
        if (digitalRead(BTN_OK) == LOW && (millis() - lastPress > 350)) {
            beep(1500, 60);
            if (cursor == 0) result = -1;       // BACK
            else             result = cursor - 1;
        }

        delay(10);
    }

    // Espera a liberação do OK
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);

    return result;
}