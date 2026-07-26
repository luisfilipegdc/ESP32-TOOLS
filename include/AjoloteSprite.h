#ifndef AJOLOTE_SPRITE_H
#define AJOLOTE_SPRITE_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  AXOLOTE SPRITE · mascote oficial do firmware
//  · Bitmap monocromático 96x80 pixels (960 bytes em PROGMEM)
//  · Compartido entre SplashScreen, About y Screensaver
// ═══════════════════════════════════════════════════════════════════════════

#define AJOLOTE_WIDTH   96
#define AJOLOTE_HEIGHT  80
#define AJOLOTE_BYTES   960

// Bitmap exportado (definido em AjoloteSprite.cpp)
extern const uint8_t AJOLOTE_BMP[AJOLOTE_BYTES];

// Desenha uma única linha do axolote em (x0, y0+row) usando a cor dada.
// Usado pela animação scan-in do splash.
void drawAjoloteRow(int x0, int y0, int row, uint16_t color);

// Desenha o axolote completo em tamanho original (96x80) em (x0, y0).
void drawAjoloteFull(int x0, int y0, uint16_t color);

// Desenha o axolote escalado por um fator inteiro (1=normal, 2=dobro, etc).
// Para escalas menores que 1.0, usa drawAjoloteHalf (mais eficiente).
void drawAjoloteScaled(int x0, int y0, uint16_t color, int scale);

// Desenha o axolote pela metade do tamanho (48x40) — versão otimizada
// que pega 1 a cada 2 pixels em cada eixo.
void drawAjoloteHalf(int x0, int y0, uint16_t color);

#endif