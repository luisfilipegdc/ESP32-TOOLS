#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <Arduino.h>
#include "Icons.h"

// ═══════════════════════════════════════════════════════════════════════════
//  MENU SYSTEM · carrossel principal + submenus hierárquicos
//
//  Uso a partir do main.cpp:
//      runMainMenu();   // loop infinito, nunca retorna
//
//  Uso a partir de ferramentas que precisem de listas/submenus próprios:
//      int sel = runSubMenu("WIFI TOOLS", items, 4);
//      if (sel == -1) return;   // usuário escolheu BACK
//      switch (sel) { ... }
// ═══════════════════════════════════════════════════════════════════════════

// ── Entrada do carrossel principal ────────────────────────────────────────
struct MainMenuEntry {
    const char* title;           // Nome da categoria (ex: "WIFI TOOLS")
    const char* subtitle;        // Descrição curta (ex: "Scan, Deauth, ...")
    IconID      icon;            // ID do ícone a mostrar
    void        (*handler)();    // Função a chamar ao pressionar OK
};

// ── API pública ───────────────────────────────────────────────────────────

// Carrossel principal. Chame-o do loop() ou setup(); não retorna.
void runMainMenu();

// Submenu tipo lista (scroll vertical). Retorna:
//   · -1 se o usuário escolheu BACK ou segurou o OK
//   · índice 0..count-1 do item selecionado
int  runSubMenu(const char* title, const char* items[], int count);

#endif