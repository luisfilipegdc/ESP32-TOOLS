#ifndef BATTERY_H
#define BATTERY_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  BATTERY MONITOR (opcional)
//  · Lê a tensão da bateria LiPo 1S no GPIO 36 através de um divisor 2x 100kΩ.
//  · Habilitado por BATTERY_MONITOR_ENABLED em Pins.h (padrão: desligado).
//  · Todas as funções são no-op / valores neutros quando desligado, então os
//    chamadores (headers) podem invocá-las incondicionalmente.
// ═══════════════════════════════════════════════════════════════════════════

// Tensão da bateria em volts (já compensa o divisor). 0.0 se desabilitado.
float batteryVoltage();

// Porcentagem estimada 0..100 para uma célula LiPo. -1 se desabilitado.
int batteryPercent();

// Largura em pixels que o indicador reserva num header (0 se desabilitado).
// Útil para posicionar outros elementos sem colidir com a bateria.
int batteryIndicatorWidth();

// Desenha o indicador (corpo + preenchimento colorido por nível) com o canto
// superior-esquerdo em (x, y). No-op se BATTERY_MONITOR_ENABLED == 0.
void drawBatteryIndicator(int x, int y);

#endif
