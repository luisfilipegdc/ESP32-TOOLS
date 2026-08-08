// Pins.h
#pragma once

// ── Botões ──────────────────────────
// ATENCAO (hardware): GPIO 34 e 35 sao ENTRADA-ONLY e NAO tem pull-up interno.
// Com a tela paralela ocupando todos os pinos com pull-up, os botoes UP/OK
// PRECISAM de um resistor de PULL-UP EXTERNO (10k entre o pino e 3V3); o botao
// liga o pino ao GND. O DOWN (GPIO23) tem pull-up interno e dispensa resistor.
// (Botao pressionado = nivel LOW, como o codigo espera.)
#define BTN_UP    34   // precisa de pull-up externo 10k -> 3V3
#define BTN_OK    35   // precisa de pull-up externo 10k -> 3V3
#define BTN_DOWN  23   // pull-up interno OK

// ── Buzzer ───────────────────────────
#define BUZZER_PIN 22

// ── NRF24L01 ─────────────────────────
#define CE_PIN   21
#define CSN_PIN  32
#define SCK_PIN  25
#define MISO_PIN 26
#define MOSI_PIN 33

// ── Bateria (opcional) ───────────────
// Requer um divisor de tensao 2x 100kohm da bateria ao GPIO 36 (ADC1, so-entrada).
// Deixe DESABILITADO (0) se voce NAO soldou o divisor: sem ele o GPIO 36 fica
// flutuando e o indicador mostraria valores falsos. Mude para 1 apos ligar o
// divisor no hardware. (pode ser sobreposto por -DBATTERY_MONITOR_ENABLED=1)
#define BATTERY_ADC_PIN          36
#ifndef BATTERY_MONITOR_ENABLED
#define BATTERY_MONITOR_ENABLED  0
#endif

// ── Cartao SD (opcional) ─────────────
// Compartilha o barramento SPI do NRF24 (SCK25/MISO26/MOSI33) com um CS proprio.
// Habilite com SD_ENABLED=1 (ou -DSD_ENABLED=1). FORMATE o cartao em FAT32
// (cartoes de 64GB+ vem em exFAT, que a lib SD do ESP32 le mal).
// GPIO 0 e um pino "strapping": funciona como CS (idle HIGH), mas se tiver
// problema de boot, escolha outro pino de saida livre e ajuste SD_CS_PIN.
#ifndef SD_ENABLED
#define SD_ENABLED   0
#endif
#ifndef SD_CS_PIN
#define SD_CS_PIN    0
#endif
