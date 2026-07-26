#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  WIFI CONFIG · módulo reutilizável de conexão WiFi
//  · Salva SSID/password no NVS (namespace "wificonfig")
//  · Tenta auto-conexão se houver credenciais
//  · UI de scan + seleção + teclado virtual para a password
//  · Reutilizável: qualquer ferramenta pode chamar wifiConfigConnect()
// ═══════════════════════════════════════════════════════════════════════════

// Conecta ao WiFi mostrando a UI conforme necessário.
// Tenta as credenciais salvas primeiro. Se falhar ou não houver, abre a UI.
//
// Returns:
//   true  = conectado (WiFi.status() == WL_CONNECTED)
//   false = usuário cancelou ou erro irrecuperável
bool wifiConfigConnect();

// Apaga as credenciais salvas no NVS (útil para "Esquecer rede")
void wifiConfigForget();

// Retorna o SSID salvo no NVS, ou "" se não houver
String wifiConfigGetSavedSSID();

// True se houver credenciais salvas (não necessariamente válidas)
bool wifiConfigHasSaved();

#endif