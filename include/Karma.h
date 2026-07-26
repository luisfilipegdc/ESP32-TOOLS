#ifndef KARMA_H
#define KARMA_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  KARMA ATTACK · responde com beacons aos probes capturados
//  · Reusa a lista do Probe Sniffer
//  · Anuncia cada SSID buscado como red abierta disponible
//  · Channel hopping 1 → 6 → 11
//  · Dispositivos com redes abertas salvas podem se auto-conectar
// ═══════════════════════════════════════════════════════════════════════════

void runKarma();

#endif