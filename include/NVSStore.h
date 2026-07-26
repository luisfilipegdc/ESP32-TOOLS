#ifndef NVS_STORE_H
#define NVS_STORE_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  NVSStore · wrapper simples sobre ESP32 Preferences (NVS)
//  · Persistência em flash: sobrevive a reinícios e quedas de energia
//  · Chaves limitadas a 15 caracteres (limitação do NVS)
//  · API minimalista: get com default, set, commit
// ═══════════════════════════════════════════════════════════════════════════

// Inicializa o namespace do NVS. Chamar UMA ÚNICA VEZ no setup().
void nvsBegin();

// Fechar (opcional, ao final do programa)
void nvsEnd();

// ── Lectura ───────────────────────────────────────────────────────────────
//   Retornam o valor salvo, ou `defaultValue` se a chave não existir.
bool          nvsGetBool(const char* key, bool defaultValue);
int           nvsGetInt(const char* key, int defaultValue);
unsigned long nvsGetULong(const char* key, unsigned long defaultValue);
String        nvsGetString(const char* key, const String& defaultValue);

// ── Escritura ─────────────────────────────────────────────────────────────
//   Salvam imediatamente na flash.
void nvsSetBool(const char* key, bool value);
void nvsSetInt(const char* key, int value);
void nvsSetULong(const char* key, unsigned long value);
void nvsSetString(const char* key, const String& value);

// ── Utilidades ────────────────────────────────────────────────────────────
void nvsErase(const char* key);      // apaga uma chave específica
void nvsEraseAll();                  // ⚠️ apaga TODAS as preferências

#endif