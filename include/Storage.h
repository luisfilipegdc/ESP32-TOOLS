#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  STORAGE · cartão SD (opcional)
//  · Compartilha o barramento SPI do NRF24 (SCK/MISO/MOSI) + CS próprio.
//  · Habilitado por SD_ENABLED em Pins.h (padrão: desligado).
//  · Cartão deve estar em FAT32.
//  · Quando desligado, tudo vira no-op / valor neutro, então os chamadores
//    podem invocar sem #ifdef.
//
//  Fase 1 (este módulo): montar o cartão e escrever linhas em arquivos.
//  Próximos passos: export de logs do Evil Portal, dump de capturas .pcap.
// ═══════════════════════════════════════════════════════════════════════════

// Monta o cartão SD. Retorna true se montou. No-op/false se desabilitado.
bool storageBegin();

// True se o cartão está montado e pronto.
bool storageAvailable();

// Anexa uma linha a um arquivo (cria se não existir). false se indisponível.
bool storageAppendLine(const char* path, const String& line);

// Espaço livre estimado em MB (0 se indisponível).
uint32_t storageFreeMB();

#endif
