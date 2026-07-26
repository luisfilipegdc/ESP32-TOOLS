#ifndef PROBE_SNIFFER_H
#define PROBE_SNIFFER_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  PROBE REQUEST SNIFFER · captura os SSIDs que os celulares próximos procuram
//  · Modo promiscuo, filtra solo probe requests (subtype 0x04)
//  · Deduplica SSIDs e conta quantas vezes cada um foi visto
//  · Channel hopping (1 → 6 → 11) a cada 2 segundos
//  · Lista navegável com SSID + count + último RSSI + último visto
// ═══════════════════════════════════════════════════════════════════════════

void runProbeSniffer();

// API para o KARMA Attack reutilizar a lista capturada (próxima feature)
struct ProbeEntry {
    char     ssid[33];
    uint16_t count;
    int8_t   rssi;
    uint32_t lastSeenMs;
};

int  probeSnifferGetCount();
bool probeSnifferGet(int idx, ProbeEntry& out);

#endif