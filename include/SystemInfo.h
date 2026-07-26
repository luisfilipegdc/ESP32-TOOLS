#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  SYSTEM INFO · tela de diagnóstico do dispositivo
//  · Mostra firmware, hardware e runtime stats ao vivo
//  · Auto-refresh cada 500ms (uptime, heap, temperatura)
//  · Sair com OK segurado ~300ms
// ═══════════════════════════════════════════════════════════════════════════

// Versão do firmware (mudar ao lançar novas releases)
#define FW_NAME     "ESP32-TOOLS"
#define FW_VERSION  "v1.0"

void runSystemInfo();

#endif