#ifndef PEPE_DRAW_H
#define PEPE_DRAW_H

#include <Arduino.h>
#include <TFT_eSPI.h>

// ═══════════════════════════════════════════════════════════════════════════
//  PEPE-DRAW v2  ·  Biblioteca de renderização de texto bitmap
//  · 2 fontes próprias: SMALL (5x7) e BIG (8x12)
//  · Largura variável por caractere (kerning real)
//  · Descenders reales (g j p q y)
//  · Suporte a espanhol: á é í ó ú ü ñ Ñ Á É Í Ó Ú Ü ¿ ¡
//  · UTF-8 aware
// ═══════════════════════════════════════════════════════════════════════════

// ── Colores de UI ─────────────────────────────────────────────────────────
#define UI_MAIN    TFT_WHITE
#define UI_BG      TFT_BLACK
#define UI_ACCENT  0x7BEF   // Gris
#define UI_CURSOR  TFT_WHITE
#define UI_SELECT  0xFA20   // Laranja-vermelho forte (highlight ao selecionar)

extern TFT_eSPI tft;

// ── Tipos de fonte ───────────────────────────────────────────────────────
enum FontType {
    FONT_SMALL = 0,   // 5 largura × 7 altura (compacta, legível)
    FONT_BIG   = 1    // 8 largura × 12 altura (títulos, headers)
};

// ───────────────────────────────────────────────────────────────────────────
//  API retrocompatível (não quebra código existente)
//  drawCharCustom / drawStringCustom → usan FONT_SMALL internamente
// ───────────────────────────────────────────────────────────────────────────
void drawCharCustom(int x, int y, char c, uint16_t color, int size);
void drawStringCustom(int x, int y, String txt, uint16_t color, int size);

// ───────────────────────────────────────────────────────────────────────────
//  API nueva
// ───────────────────────────────────────────────────────────────────────────

// Desenha com a fonte BIG (8x12)
void drawStringBig(int x, int y, const String& txt, uint16_t color, int size);

// Calcula a largura em pixels de um texto (útil para centralizar ou alinhar)
int  getTextWidth(const String& txt, int size, FontType font = FONT_SMALL);

// Altura em pixels da fonte (para calcular posições verticais)
int  getFontHeight(int size, FontType font = FONT_SMALL);

// Desenha centralizado horizontalmente na tela (largura 320)
void drawStringCentered(int y, const String& txt, uint16_t color,
                        int size, FontType font = FONT_SMALL);

// Desenha alinhado à direita (xRight = borda direita do texto)
void drawStringRight(int xRight, int y, const String& txt, uint16_t color,
                     int size, FontType font = FONT_SMALL);

#endif