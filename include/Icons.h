#ifndef ICONS_H
#define ICONS_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  ICONS · Bitmaps pixel-art para o menu principal
//  · Formato: 64x64 pixels monocromo
//  · Cada byte = 8 pixels horizontais (bit MSB = esquerda)
//  · 64 * 64 / 8 = 512 bytes por ícone
//  · Desenháveis com cor personalizada (branco normal, laranja ao selecionar)
// ═══════════════════════════════════════════════════════════════════════════

#define ICON_SIZE       64
#define ICON_BYTES      (ICON_SIZE * ICON_SIZE / 8)   // 512 bytes

// ── IDs dos ícones ─────────────────────────────────────────────────────────
enum IconID {
    ICON_WIFI = 0,
    ICON_RADIO,
    ICON_BLUETOOTH,
    ICON_MONITOR,
    ICON_SYSTEM,
    ICON_COUNT
};

// Desenha um ícone centralizado em (cx, cy) com a cor dada.
// Os pixels fora do range vertical [yMin, yMax] são descartados (clipping).
// Usa drawIcon(..., 0, 239) si no necesitas clipping.
void drawIcon(int cx, int cy, IconID id, uint16_t color,
              int yMin = 0, int yMax = 239);

#endif