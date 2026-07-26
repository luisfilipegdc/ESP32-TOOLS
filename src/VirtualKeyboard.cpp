#include "VirtualKeyboard.h"
#include <TFT_eSPI.h>
#include "PepeDraw.h"
#include "Pins.h"
#include "SoundUtils.h"

extern TFT_eSPI tft;

// ═══════════════════════════════════════════════════════════════════════════
//  LAYOUT DO TECLADO
// ═══════════════════════════════════════════════════════════════════════════

// 4 linhas alfanuméricas × 10 colunas
static const char* KB_ROWS_LOWER[] = {
    "1234567890",
    "qwertyuiop",
    "asdfghjklñ",
    "zxcvbnm.-_"
};

static const char* KB_ROWS_UPPER[] = {
    "!@#$%^&*()",          // shift de números → símbolos comunes
    "QWERTYUIOP",
    "ASDFGHJKLÑ",
    "ZXCVBNM,/+"           // shift de la última fila → más símbolos
};

// Especiais na linha 4 (índices 0-4)
enum SpecialKey {
    KEY_SHIFT = 0,
    KEY_SPACE = 1,
    KEY_DEL   = 2,
    KEY_OK    = 3,
    KEY_CANCEL = 4
};

static const char* SPECIAL_LABELS[] = {
    "SHIFT", "SPACE", "DEL", "OK", "X"
};

// ═══════════════════════════════════════════════════════════════════════════
//  GEOMETRIA
// ═══════════════════════════════════════════════════════════════════════════
#define KB_KEY_W      28        // ancho de tecla normal
#define KB_KEY_H      22        // alto de tecla
#define KB_GAP        2         // separación entre teclas
#define KB_START_X    10        // X del inicio del teclado
#define KB_START_Y    96        // Y del inicio del teclado

// Largura total = 10 * (28 + 2) - 2 = 298 → cabe em 320 com margem
// Altura total = 5 linhas × 24 + alguns pixels = ~120

// ═══════════════════════════════════════════════════════════════════════════
//  ESTADO
// ═══════════════════════════════════════════════════════════════════════════
static int     g_cursorRow = 1;     // 0..4 (4 = fila especiales)
static int     g_cursorCol = 0;     // 0..9 (0..4 en fila especial)
static bool    g_shiftActive = false;
static String  g_buffer = "";
static int     g_maxLen = 62;
static bool    g_maskInput = false;

// ═══════════════════════════════════════════════════════════════════════════
//  HELPERS
// ═══════════════════════════════════════════════════════════════════════════

// Dada uma coluna alfanumérica (0-9), retorna o índice da tecla
// especial correspondente na linha 4 (0-4)
static int alphaColToSpecialCol(int col) {
    return col / 2;   // cols 0,1 → SHIFT; 2,3 → SPACE; 4,5 → DEL; 6,7 → OK; 8,9 → CANCEL
}

// Dada uma tecla especial (0-4), retorna a coluna alfanumérica inicial (0-9)
static int specialColToAlphaCol(int specialIdx) {
    return specialIdx * 2;
}

static char getCharAt(int row, int col) {
    if (row < 0 || row > 3) return 0;
    if (col < 0 || col > 9) return 0;
    const char* rowStr = g_shiftActive ? KB_ROWS_UPPER[row] : KB_ROWS_LOWER[row];
    return rowStr[col];
}

// ═══════════════════════════════════════════════════════════════════════════
//  DESENHO
// ═══════════════════════════════════════════════════════════════════════════

static void drawKey(int row, int col, bool selected) {
    int x = KB_START_X + col * (KB_KEY_W + KB_GAP);
    int y = KB_START_Y + row * (KB_KEY_H + KB_GAP);

    uint16_t bg = selected ? UI_SELECT : TFT_BLACK;
    uint16_t fg = selected ? UI_BG     : UI_MAIN;
    uint16_t border = selected ? UI_SELECT : UI_ACCENT;

    tft.fillRect(x, y, KB_KEY_W, KB_KEY_H, bg);
    tft.drawRect(x, y, KB_KEY_W, KB_KEY_H, border);

    char c = getCharAt(row, col);
    if (c == 0) return;

    char buf[2] = {c, 0};
    int charW = 6 * 2;   // size 2, ancho aprox 6px por char
    int tx = x + (KB_KEY_W - charW) / 2 + 1;
    int ty = y + (KB_KEY_H - 12) / 2;
    drawStringCustom(tx, ty, String(buf), fg, 2);
}

static void drawSpecialKey(int specialIdx, bool selected) {
    int startCol = specialColToAlphaCol(specialIdx);
    int x = KB_START_X + startCol * (KB_KEY_W + KB_GAP);
    int y = KB_START_Y + 4 * (KB_KEY_H + KB_GAP);
    int w = (KB_KEY_W * 2) + KB_GAP;   // 2 columnas de ancho
    int h = KB_KEY_H + 4;              // un poquito más alto

    bool isShift = (specialIdx == KEY_SHIFT);
    bool shiftLit = isShift && g_shiftActive;

    uint16_t bg, fg, border;
    if (selected) {
        bg = UI_SELECT;
        fg = UI_BG;
        border = UI_SELECT;
    } else if (shiftLit) {
        bg = TFT_GREEN;
        fg = UI_BG;
        border = TFT_GREEN;
    } else {
        bg = TFT_BLACK;
        fg = UI_MAIN;
        border = UI_ACCENT;

        // Cor especial para OK e CANCEL
        if (specialIdx == KEY_OK)     border = TFT_GREEN;
        if (specialIdx == KEY_CANCEL) border = TFT_RED;
    }

    tft.fillRect(x, y, w, h, bg);
    tft.drawRect(x, y, w, h, border);

    const char* label = SPECIAL_LABELS[specialIdx];
    int labelW = strlen(label) * 6;    // size 1
    int tx = x + (w - labelW) / 2;
    int ty = y + (h - 8) / 2;
    drawStringCustom(tx, ty, String(label), fg, 1);
}

static void drawAllKeys() {
    bool inSpecialRow = (g_cursorRow == 4);

    // Desenha as 40 teclas alfanuméricas
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 10; col++) {
            bool sel = !inSpecialRow && (row == g_cursorRow) && (col == g_cursorCol);
            drawKey(row, col, sel);
        }
    }

    // Desenha as 5 teclas especiais
    int specialSelectedIdx = inSpecialRow ? alphaColToSpecialCol(g_cursorCol) : -1;
    for (int s = 0; s < 5; s++) {
        drawSpecialKey(s, s == specialSelectedIdx);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  TEXTBOX (onde é mostrado o que você está escrevendo)
// ═══════════════════════════════════════════════════════════════════════════

static void drawTextBox() {
    // Limpa a área
    tft.fillRect(10, 56, 300, 32, TFT_BLACK);
    tft.drawRect(10, 56, 300, 32, UI_MAIN);

    // Construir display string
    String display;
    if (g_maskInput) {
        for (int i = 0; i < (int)g_buffer.length(); i++) display += "*";
    } else {
        display = g_buffer;
    }

    // Cursor blink
    bool showCursor = ((millis() / 500) % 2) == 0;
    if (showCursor) display += "_";

    // Truncar si es muy largo
    int maxChars = 28;
    if (display.length() > (unsigned)maxChars) {
        display = display.substring(display.length() - maxChars);
    }

    drawStringCustom(15, 64, display, UI_MAIN, 2);

    // Counter
    String count = String(g_buffer.length()) + "/" + String(g_maxLen);
    drawStringCustom(260, 78, count, UI_ACCENT, 1);
}

static void drawHeader(const String& title, const String& subtitle) {
    tft.fillRect(0, 0, 320, 50, TFT_BLACK);
    tft.drawRect(0, 0, 320, 240, UI_MAIN);

    // Title
    drawStringBig(10, 8, title, UI_MAIN, 1);

    // Subtitle (truncado)
    String sub = subtitle;
    if (sub.length() > 38) sub = sub.substring(0, 36) + "..";
    drawStringCustom(10, 30, sub, UI_ACCENT, 1);

    tft.drawFastHLine(0, 50, 320, UI_ACCENT);
}

static void drawFooter() {
    tft.drawFastHLine(0, 224, 320, UI_ACCENT);
    drawStringCustom(8, 230, "UP/DN:NAV  OK:SELECT", UI_ACCENT, 1);
}

// ═══════════════════════════════════════════════════════════════════════════
//  NAVEGAÇÃO
//  Lógica: UP/DOWN circula verticalmente. Quando chega ao fim/início
//  da coluna, pula para a coluna seguinte/anterior e volta ao início
// ═══════════════════════════════════════════════════════════════════════════

static void cursorDown() {
    if (g_cursorRow < 4) {
        g_cursorRow++;
    } else {
        // Na linha especial. Avança coluna por coluna (sem pular).
        g_cursorCol = (g_cursorCol + 1) % 10;
        g_cursorRow = 0;
    }
}

    static void cursorUp() {
    if (g_cursorRow > 0) {
        g_cursorRow--;
    } else {
        // Na linha 0. Retrocede coluna por coluna e pula para a linha 4.
        g_cursorCol = (g_cursorCol + 9) % 10;
        g_cursorRow = 4;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  ACCIONES
// ═══════════════════════════════════════════════════════════════════════════

// Executa a tecla atual. Retorna:
//   0 = continua
//   1 = OK confirmado (terminar com o buffer)
//   2 = CANCEL (terminar com string vazia)
static int executeCurrentKey() {
    if (g_cursorRow < 4) {
        // Tecla alfanumérica
        char c = getCharAt(g_cursorRow, g_cursorCol);
        if (c == 0) return 0;
        if ((int)g_buffer.length() < g_maxLen) {
            g_buffer += c;
            // Depois de digitar com shift, desativa o shift (como teclados móveis)
            if (g_shiftActive) {
                g_shiftActive = false;
            }
            beep(2400, 25);
        } else {
            beep(800, 50);   // beep de error (lleno)
        }
        return 0;
    }

    // Linha especial
    int specialIdx = alphaColToSpecialCol(g_cursorCol);
    switch (specialIdx) {
        case KEY_SHIFT:
            g_shiftActive = !g_shiftActive;
            beep(2800, 30);
            return 0;
        case KEY_SPACE:
            if ((int)g_buffer.length() < g_maxLen) {
                g_buffer += " ";
                beep(2400, 25);
            }
            return 0;
        case KEY_DEL:
            if (g_buffer.length() > 0) {
                g_buffer.remove(g_buffer.length() - 1);
                beep(2000, 30);
            } else {
                beep(800, 50);
            }
            return 0;
        case KEY_OK:
            beep(3200, 80);
            return 1;
        case KEY_CANCEL:
            beep(1200, 80);
            return 2;
    }
    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════
//  ENTRY POINT
// ═══════════════════════════════════════════════════════════════════════════

String virtualKeyboardInput(const String& title,
                            const String& subtitle,
                            int maxLen,
                            bool maskInput) {
    // Espera a liberação do OK (caso estejamos vindo pressionando)
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);

    // Reset estado
    g_cursorRow = 1;
    g_cursorCol = 0;
    g_shiftActive = false;
    g_buffer = "";
    g_maxLen = maxLen;
    g_maskInput = maskInput;

    // Initial draw
    tft.fillScreen(TFT_BLACK);
    drawHeader(title, subtitle);
    drawTextBox();
    drawAllKeys();
    drawFooter();

    unsigned long lastBlink = millis();
    unsigned long lastBtn = 0;

    while (true) {
        // Blink cursor
        if (millis() - lastBlink > 500) {
            drawTextBox();
            lastBlink = millis();
        }

        // UP
        if (digitalRead(BTN_UP) == LOW && millis() - lastBtn > 180) {
            cursorUp();
            beep(2100, 15);
            drawAllKeys();
            lastBtn = millis();
        }

        // DOWN
        if (digitalRead(BTN_DOWN) == LOW && millis() - lastBtn > 180) {
            cursorDown();
            beep(2100, 15);
            drawAllKeys();
            lastBtn = millis();
        }

        // OK
        if (digitalRead(BTN_OK) == LOW && millis() - lastBtn > 180) {
            int result = executeCurrentKey();
            while (digitalRead(BTN_OK) == LOW) delay(5);
            delay(50);

            if (result == 1) {
                return g_buffer;
            }
            if (result == 2) {
                return "";
            }

            // Continua: redesenha tudo (shift, buffer, etc. podem ter mudado)
            drawTextBox();
            drawAllKeys();
            lastBtn = millis();
        }

        delay(15);
    }
}