#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  SCREENSAVER · ajolote caminando estilo "DVD logo"
//  · É ativado pelo menu principal após IDLE_TIMEOUT_MS sem input
//  · Sai com qualquer botão (UP/DOWN/OK)
//  · Estrellitas titilando + textos rotativos
// ═══════════════════════════════════════════════════════════════════════════

#define SCREENSAVER_IDLE_MS  30000   // 30 segundos

// Executa o screensaver. Bloqueia até o usuário tocar num botão.
// Ao retornar, o menu atual deve ser redesenhado.
void runScreensaver();

#endif