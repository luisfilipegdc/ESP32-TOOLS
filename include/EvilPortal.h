#ifndef EVIL_PORTAL_H
#define EVIL_PORTAL_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  EVIL PORTAL · captura credenciais com AP falso + portal cativo
//  · 10 SSIDs predefinidos (ISPs, cafeterias, públicos)
//  · Modo SIMPLE: AP fixo com o SSID escolhido
//  · Modo CLONE: clona a rede real + deauth simultâneo
//  · 4 plataformas de phishing (FB, Google, IG, TikTok)
//  · Logs persistentes em NVS, ver/apagar pelo menu
//  · USO EDUCATIVO/PENTESTING SOMENTE
// ═══════════════════════════════════════════════════════════════════════════

void runEvilPortal();

#endif