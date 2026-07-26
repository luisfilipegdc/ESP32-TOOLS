#ifndef BLE_SCANNER_H
#define BLE_SCANNER_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  BLE SCANNER · descubre dispositivos Bluetooth Low Energy cercanos
//  · Scan contínuo (até o usuário sair com OK-hold)
//  · Lista ordenada por RSSI (mais próximos no topo)
//  · Vendor lookup por OUI (Apple, Samsung, Xiaomi, etc.)
//  · Detalhes por dispositivo: MAC, RSSI, serviços, manufacturer data
// ═══════════════════════════════════════════════════════════════════════════

void runBLEScanner();

#endif