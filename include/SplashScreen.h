#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  SPLASH SCREEN · tela de boas-vindas ao ligar o dispositivo
//
//  Muestra:
//    · Axolote pixel-art com óculos (mascote do projeto)
//    · Título "ESP32-TOOLS" com animação type-on
//    · Autor "BY: PepeAngell"
//    · Sequência de "loading steps" com beeps ascendentes
//    · Mensagem "PRESS OK" piscando no final
//    · Espera até o usuário pressionar OK para continuar
// ═══════════════════════════════════════════════════════════════════════════

void runSplashScreen();

#endif