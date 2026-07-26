#ifndef VIRTUAL_KEYBOARD_H
#define VIRTUAL_KEYBOARD_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  TECLADO VIRTUAL · 10 colunas × 4 linhas alfanuméricas + 5 especiais
//  · Navegação: UP/DOWN coluna por coluna (vertical primeiro)
//  · SHIFT alterna maiúsculas
//  · Layout QWERTY espanhol com ñ
//  · Retorna a string digitada ou "" se foi cancelado
// ═══════════════════════════════════════════════════════════════════════════

// Mostra o teclado e retorna a string digitada pelo usuário.
// Se o usuário cancela (X), retorna string vazia.
//
// Parameters:
//   title:       título mostrado na parte superior (ex: "WIFI PASSWORD")
//   subtitle:    linha abaixo do título (ex: "Red: MiCasa_Telmex")
//   maxLen:      máximo de caracteres permitidos (62 default)
//   maskInput:   true = muestra asteriscos (***), false = muestra texto plano
//
// Returns:
//   String digitada, ou "" se foi cancelado
String virtualKeyboardInput(const String& title,
                             const String& subtitle,
                             int maxLen = 62,
                             bool maskInput = false);

#endif