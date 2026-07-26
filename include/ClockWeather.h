#ifndef CLOCK_WEATHER_H
#define CLOCK_WEATHER_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════════════════════
//  CLOCK & WEATHER
//  · NTP sync para hora exata
//  · IP geolocation (ip-api.com) para detectar a cidade
//  · Open-Meteo API para dados climáticos (sem API key)
//  · Tela com relógio grande + clima com ícones pixel art
// ═══════════════════════════════════════════════════════════════════════════

void runClockWeather();

#endif