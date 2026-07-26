// Pins.h
#pragma once

// ── Botões ──────────────────────────
#define BTN_UP    34
#define BTN_OK    35
#define BTN_DOWN  23

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
// divisor no hardware.
#define BATTERY_ADC_PIN          36
#define BATTERY_MONITOR_ENABLED  0
