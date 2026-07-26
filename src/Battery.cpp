#include "Battery.h"
#include "Pins.h"
#include <TFT_eSPI.h>
#include "PepeDraw.h"

extern TFT_eSPI tft;

#if BATTERY_MONITOR_ENABLED

// ═══════════════════════════════════════════════════════════════════════════
//  LEITURA
// ═══════════════════════════════════════════════════════════════════════════

float batteryVoltage() {
    // Média de várias leituras calibradas (mV) para reduzir ruído do ADC.
    const int N = 8;
    uint32_t accMv = 0;
    for (int i = 0; i < N; i++) {
        accMv += analogReadMilliVolts(BATTERY_ADC_PIN);
    }
    float pinV = (accMv / (float)N) / 1000.0f;   // volts no GPIO 36
    return pinV * 2.0f;                           // divisor 2x100kΩ → x2
}

int batteryPercent() {
    float v = batteryVoltage();

    // Curva aproximada de descarga de uma LiPo 1S (volts → %).
    static const struct { float v; int pct; } CURVE[] = {
        { 4.20f, 100 }, { 4.10f, 90 }, { 4.00f, 80 }, { 3.90f, 70 },
        { 3.80f, 58  }, { 3.70f, 45 }, { 3.60f, 30 }, { 3.50f, 16 },
        { 3.40f, 6   }, { 3.30f, 0  }
    };
    const int POINTS = sizeof(CURVE) / sizeof(CURVE[0]);

    if (v >= CURVE[0].v) return 100;
    for (int i = 0; i < POINTS - 1; i++) {
        if (v >= CURVE[i + 1].v) {
            float span = CURVE[i].v - CURVE[i + 1].v;
            float t = (v - CURVE[i + 1].v) / span;   // 0..1 dentro do segmento
            return (int)(CURVE[i + 1].pct +
                         t * (CURVE[i].pct - CURVE[i + 1].pct));
        }
    }
    return 0;
}

// ═══════════════════════════════════════════════════════════════════════════
//  DESENHO
// ═══════════════════════════════════════════════════════════════════════════

int batteryIndicatorWidth() {
    return 24;   // 18 corpo + 2 terminal + 4 de margem
}

void drawBatteryIndicator(int x, int y) {
    int pct = batteryPercent();
    if (pct < 0)   pct = 0;
    if (pct > 100) pct = 100;

    // Cor por nível: verde > 50%, amarelo > 20%, vermelho abaixo disso.
    uint16_t col = (pct > 50) ? TFT_GREEN
                 : (pct > 20) ? TFT_YELLOW
                              : TFT_RED;

    const int bw = 18, bh = 10;

    // Corpo + terminal (nub) à direita.
    tft.drawRect(x, y, bw, bh, UI_MAIN);
    tft.fillRect(x + bw, y + 3, 2, 4, UI_MAIN);

    // Preenchimento proporcional.
    int innerW = bw - 2;
    int fillW = (int)(innerW * pct / 100.0f);
    if (fillW < 0)      fillW = 0;
    if (fillW > innerW) fillW = innerW;

    tft.fillRect(x + 1, y + 1, fillW, bh - 2, col);
    // Limpa o restante do interior (fundo preto) para redesenhos.
    if (fillW < innerW) {
        tft.fillRect(x + 1 + fillW, y + 1, innerW - fillW, bh - 2, TFT_BLACK);
    }
}

#else   // BATTERY_MONITOR_ENABLED == 0 → stubs neutros

float batteryVoltage()        { return 0.0f; }
int   batteryPercent()        { return -1;   }
int   batteryIndicatorWidth() { return 0;    }
void  drawBatteryIndicator(int /*x*/, int /*y*/) { /* desabilitado */ }

#endif
