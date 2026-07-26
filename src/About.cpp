#include "About.h"
#include <TFT_eSPI.h>
#include "PepeDraw.h"
#include "Pins.h"
#include "SoundUtils.h"
#include "NVSStore.h"
#include "SystemInfo.h"
#include "AjoloteSprite.h"

extern TFT_eSPI tft;

// ═══════════════════════════════════════════════════════════════════════════
//  CONFIG
// ═══════════════════════════════════════════════════════════════════════════
#define VIEWPORT_TOP    34     // onde começa o viewport (abaixo do header)
#define VIEWPORT_BOTTOM 218    // onde termina (acima do footer)
#define SCROLL_STEP     20

static int g_scrollY = 0;
static int g_maxScroll = 0;

// ═══════════════════════════════════════════════════════════════════════════
//  HELPERS DE DESENHO COM CLIPPING (não desenha fora do viewport)
// ═══════════════════════════════════════════════════════════════════════════

// Desenha o texto SOMENTE se ele cabe inteiramente dentro do viewport.
// Se estiver parcialmente fora, não desenha (evita sujar header/footer).
static void drawScrollableText(int yContent, int x, const String& text,
                                uint16_t color, int size) {
    int yScreen = VIEWPORT_TOP + (yContent - g_scrollY);
    int textH = (size == 1) ? 7 : (size * 8);

    // Se estiver completamente fora do viewport, não desenha
    if (yScreen + textH < VIEWPORT_TOP) return;
    if (yScreen > VIEWPORT_BOTTOM) return;

    // Se estiver parcialmente fora, também não — evita que vaze
    if (yScreen < VIEWPORT_TOP) return;
    if (yScreen + textH > VIEWPORT_BOTTOM) return;

    drawStringCustom(x, yScreen, text, color, size);
}

static void drawScrollableLine(int yContent, uint16_t color) {
    int yScreen = VIEWPORT_TOP + (yContent - g_scrollY);
    if (yScreen < VIEWPORT_TOP || yScreen > VIEWPORT_BOTTOM) return;
    tft.drawFastHLine(15, yScreen, 290, color);
}

// Axolote em meia escala (48x40). Recorta linhas individuais se ficarem
// parcialmente fora do viewport.
static void drawScrollableAjolote(int yContent) {
    const int W = 48;
    const int H = 40;
    int x = (320 - W) / 2;
    int yBase = VIEWPORT_TOP + (yContent - g_scrollY);

    // Se estiver completamente fora, sair
    if (yBase + H < VIEWPORT_TOP) return;
    if (yBase > VIEWPORT_BOTTOM) return;

    // Desenha linha por linha, pulando as que estão fora do viewport
    int bytesPerRow = AJOLOTE_WIDTH / 8;
    for (int r = 0; r < AJOLOTE_HEIGHT; r += 2) {
        int outY = yBase + r / 2;
        if (outY < VIEWPORT_TOP) continue;     // acima do viewport
        if (outY > VIEWPORT_BOTTOM) break;     // já passamos do viewport

        for (int byteIdx = 0; byteIdx < bytesPerRow; byteIdx++) {
            uint8_t bits = pgm_read_byte(
                &AJOLOTE_BMP[r * bytesPerRow + byteIdx]);
            if (bits == 0) continue;
            for (int bit = 0; bit < 8; bit += 2) {
                if (bits & (0x80 >> bit)) {
                    int outX = x + (byteIdx * 8 + bit) / 2;
                    tft.drawPixel(outX, outY, UI_MAIN);
                }
            }
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  CONTEÚDO PRINCIPAL
// ═══════════════════════════════════════════════════════════════════════════

static void drawAboutContent() {
    // Limpa o viewport (NÃO o header nem o footer)
    tft.fillRect(2, VIEWPORT_TOP, 316, VIEWPORT_BOTTOM - VIEWPORT_TOP,
                 TFT_BLACK);

    int y = 5;   // posição Y dentro do conteúdo virtual

    // ─── Título grande ───
    String title = "ESP32-TOOLS";
    int tw = title.length() * 8 * 3;   // size 3 com FONT_BIG
    drawScrollableText(y, (320 - tw) / 2, title, UI_MAIN, 3);
    y += 32;

    // ─── Versão ───
    String version = String(FW_VERSION);
    int vw = version.length() * 6 * 2;
    drawScrollableText(y, (320 - vw) / 2, version, UI_SELECT, 2);
    y += 28;

    drawScrollableLine(y, UI_ACCENT);
    y += 12;

    // ─── Axolote (48x40) ───
    drawScrollableAjolote(y);
    y += 50;

    drawScrollableLine(y, UI_ACCENT);
    y += 14;

    // ─── Autor ───
    drawScrollableText(y, 70, "By PepeAngell", TFT_YELLOW, 2);
    y += 28;

    drawScrollableText(y, 30, "Jose Angel", UI_MAIN, 2);
    y += 22;
    drawScrollableText(y, 30, "Chavez Felix", UI_MAIN, 2);
    y += 28;

    drawScrollableText(y, 30, "Los Mochis, Sinaloa", UI_ACCENT, 1);
    y += 12;
    drawScrollableText(y, 30, "Mexico", UI_ACCENT, 1);
    y += 18;

    drawScrollableLine(y, UI_ACCENT);
    y += 14;

    // ─── Redes sociais ───
    drawScrollableText(y, 30, "REDES SOCIAIS", UI_MAIN, 1);
    y += 20;

    drawScrollableText(y, 30, "IG:", TFT_CYAN, 2);
    drawScrollableText(y, 80, "@pepeangelll", UI_MAIN, 2);
    y += 26;

    drawScrollableText(y, 30, "FB:", 0x041F, 2);
    drawScrollableText(y, 80, "/esp32tools", UI_MAIN, 2);
    y += 26;

    drawScrollableText(y, 30, "GH:", 0xA81F, 2);
    drawScrollableText(y, 80, "/pepeangell5", UI_MAIN, 2);
    y += 30;

    drawScrollableLine(y, UI_ACCENT);
    y += 14;

    // ─── Boot count ───
    int boots = nvsGetInt("boot_cnt", 0);
    String bootText = "Iniciado " + String(boots) + " vezes";
    int bw = bootText.length() * 6;
    drawScrollableText(y, (320 - bw) / 2, bootText, UI_ACCENT, 1);
    y += 18;

    drawScrollableLine(y, UI_ACCENT);
    y += 14;

    // ─── Citação / filosofia ───
    drawScrollableText(y, 30, "\"O conhecimento", TFT_GREEN, 2);
    y += 22;
    drawScrollableText(y, 30, "deve ser livre.\"", TFT_GREEN, 2);
    y += 32;

    drawScrollableText(y, 80, "HECHO", UI_ACCENT, 1);
    y += 12;
    drawScrollableText(y, 100, "NO MÉXICO", UI_ACCENT, 1);
    y += 25;

    // Calcula o max scroll
    int viewportH = VIEWPORT_BOTTOM - VIEWPORT_TOP;
    g_maxScroll = y - viewportH;
    if (g_maxScroll < 0) g_maxScroll = 0;
}

// ═══════════════════════════════════════════════════════════════════════════
//  HEADER E FOOTER (redesenhados SEMPRE por cima para evitar manchas)
// ═══════════════════════════════════════════════════════════════════════════

static void drawHeader() {
    tft.fillRect(0, 0, 320, VIEWPORT_TOP, TFT_BLACK);
    tft.drawRect(0, 0, 320, 240, UI_MAIN);
    drawStringCustom(110, 10, "ABOUT", UI_MAIN, 3);
    tft.drawFastHLine(2, VIEWPORT_TOP, 316, UI_ACCENT);
}

static void drawFooter() {
    tft.fillRect(0, VIEWPORT_BOTTOM, 320, 240 - VIEWPORT_BOTTOM, TFT_BLACK);
    tft.drawFastHLine(2, VIEWPORT_BOTTOM, 316, UI_ACCENT);

    // Redesenha as bordas laterais caso tenham sido sujas
    tft.drawFastVLine(0, 0, 240, UI_MAIN);
    tft.drawFastVLine(319, 0, 240, UI_MAIN);
    tft.drawFastHLine(0, 239, 320, UI_MAIN);

    if (g_maxScroll > 0) {
        if (g_scrollY == 0) {
            drawStringCustom(10, 226, "DOWN: VER MAIS  OK: VOLTAR",
                             UI_ACCENT, 1);
        } else if (g_scrollY >= g_maxScroll) {
            drawStringCustom(10, 226, "UP: SUBIR  OK: VOLTAR",
                             UI_ACCENT, 1);
        } else {
            drawStringCustom(10, 226, "UP/DN: SCROLL  OK: VOLTAR",
                             UI_ACCENT, 1);
        }

        // Indicador de scroll lateral
        int trackTop = VIEWPORT_TOP + 5;
        int trackBot = VIEWPORT_BOTTOM - 5;
        int trackH = trackBot - trackTop;
        int totalContent = g_maxScroll + (VIEWPORT_BOTTOM - VIEWPORT_TOP);
        int barH = (trackH * (VIEWPORT_BOTTOM - VIEWPORT_TOP)) / totalContent;
        if (barH < 10) barH = 10;
        int barY = trackTop;
        if (g_maxScroll > 0) {
            barY = trackTop + (g_scrollY * (trackH - barH)) / g_maxScroll;
        }
        // Limpa o track antes
        tft.fillRect(310, trackTop, 6, trackH, TFT_BLACK);
        tft.drawFastVLine(312, trackTop, trackH, UI_ACCENT);
        tft.fillRect(310, barY, 5, barH, UI_SELECT);
    } else {
        drawStringCustom(110, 226, "OK: VOLTAR", UI_ACCENT, 1);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  REDESENHO COMPLETO (ordem importa: conteúdo → header → footer)
// ═══════════════════════════════════════════════════════════════════════════

static void redrawAll() {
    drawAboutContent();    // 1. conteúdo rolável (pode sujar as bordas)
    drawHeader();          // 2. header por cima → cobre manchas em cima
    drawFooter();          // 3. footer por cima → cobre manchas embaixo
}

// ═══════════════════════════════════════════════════════════════════════════
//  ENTRY POINT
// ═══════════════════════════════════════════════════════════════════════════

void runAbout() {
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);

    g_scrollY = 0;

    // Beep de entrada (jingle dos créditos)
    beep(2400, 60); delay(40);
    beep(3000, 60); delay(40);
    beep(3600, 100);

    tft.fillScreen(TFT_BLACK);
    redrawAll();

    unsigned long lastBtn = 0;

    while (true) {
        if (digitalRead(BTN_OK) == LOW && millis() - lastBtn > 200) {
            beep(1800, 50); delay(30);
            beep(1200, 80);
            while (digitalRead(BTN_OK) == LOW) delay(5);
            delay(100);
            return;
        }

        if (digitalRead(BTN_UP) == LOW && millis() - lastBtn > 150) {
            if (g_scrollY > 0) {
                g_scrollY -= SCROLL_STEP;
                if (g_scrollY < 0) g_scrollY = 0;
                beep(2200, 20);
                redrawAll();
            }
            lastBtn = millis();
        }

        if (digitalRead(BTN_DOWN) == LOW && millis() - lastBtn > 150) {
            if (g_scrollY < g_maxScroll) {
                g_scrollY += SCROLL_STEP;
                if (g_scrollY > g_maxScroll) g_scrollY = g_maxScroll;
                beep(2200, 20);
                redrawAll();
            }
            lastBtn = millis();
        }

        delay(15);
    }
}