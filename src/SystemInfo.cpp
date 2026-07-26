#include "SystemInfo.h"
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <esp_system.h>
#include <esp_chip_info.h>
#include <esp_mac.h>
#include "PepeDraw.h"
#include "Pins.h"
#include "SoundUtils.h"
#include "NVSStore.h"

extern TFT_eSPI tft;

// ═══════════════════════════════════════════════════════════════════════════
//  LEITURA DA TEMPERATURA INTERNA
//  O ESP32 tem um sensor de temperatura interno acessível via função
//  ROM (não documentada oficialmente, mas estável e amplamente usada).
// ═══════════════════════════════════════════════════════════════════════════
#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

static float readChipTemperatureC() {
    // Leitura raw (resultado em °F aproximado, convertemos para °C)
    uint8_t raw = temprature_sens_read();
    float fahrenheit = (float)raw;
    return (fahrenheit - 32.0f) * 5.0f / 9.0f;
}

// ═══════════════════════════════════════════════════════════════════════════
//  FORMATADORES
// ═══════════════════════════════════════════════════════════════════════════

// Uptime formatado HH:MM:SS
static String formatUptime(unsigned long ms) {
    unsigned long totalSec = ms / 1000;
    unsigned long hours = totalSec / 3600;
    unsigned long mins  = (totalSec % 3600) / 60;
    unsigned long secs  = totalSec % 60;

    char buf[12];
    snprintf(buf, sizeof(buf), "%02lu:%02lu:%02lu", hours, mins, secs);
    return String(buf);
}

// Formata um endereço MAC em AA:BB:CC:DD:EE:FF
static String formatMAC(const uint8_t mac[6]) {
    char buf[18];
    snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return String(buf);
}

// Nome do chip conforme esp_chip_info_t
static const char* chipModelName(esp_chip_model_t model) {
    switch (model) {
        case CHIP_ESP32:    return "ESP32";
        case CHIP_ESP32S2:  return "ESP32-S2";
        case CHIP_ESP32S3:  return "ESP32-S3";
        case CHIP_ESP32C3:  return "ESP32-C3";
        case CHIP_ESP32H2:  return "ESP32-H2";
        default:            return "Unknown";
    }
}

// Formata KB com 0 casas decimais
static String formatKB(uint32_t bytes) {
    return String(bytes / 1024) + " KB";
}

static String formatMB(uint32_t bytes) {
    return String(bytes / (1024 * 1024)) + " MB";
}

// ═══════════════════════════════════════════════════════════════════════════
//  DESENHO
// ═══════════════════════════════════════════════════════════════════════════

// Desenha a moldura estática (título, separadores, section headers, footer).
// Chamado apenas uma vez ao entrar.
static void drawStaticLayout() {
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(0, 0, 320, 240, UI_MAIN);

    // Header
    drawStringBig(10, 8, "SYSTEM INFO", UI_MAIN, 1);
    tft.drawFastHLine(0, 30, 320, UI_ACCENT);

    // Section headers (estáticos)
    drawStringCustom(10, 38,  "FIRMWARE",  UI_SELECT, 1);
    drawStringCustom(10, 82,  "HARDWARE",  UI_SELECT, 1);
    drawStringCustom(10, 158, "RUNTIME",   UI_SELECT, 1);

    // Footer
    tft.drawFastHLine(0, 218, 320, UI_ACCENT);
    drawStringCustom(10, 225, "OK (HOLD): BACK TO MENU", UI_ACCENT, 1);
}

// Desenha a informação estática (não muda em runtime)
static void drawStaticInfo() {
    esp_chip_info_t chip;
    esp_chip_info(&chip);

    uint8_t macWifi[6];
    uint8_t macBT[6];
    esp_read_mac(macWifi, ESP_MAC_WIFI_STA);
    esp_read_mac(macBT,   ESP_MAC_BT);

    // ── FIRMWARE ────────────────────────────────────────────────────────
    drawStringCustom(20, 50,
        "Version: " + String(FW_NAME) + " " + String(FW_VERSION),
        UI_MAIN, 1);
    drawStringCustom(20, 62,
        "Built:   " + String(__DATE__),
        UI_ACCENT, 1);

    // ── HARDWARE ────────────────────────────────────────────────────────
    drawStringCustom(20, 94,
        "Chip:    " + String(chipModelName(chip.model)) +
        " rev" + String(chip.revision),
        UI_MAIN, 1);

    drawStringCustom(20, 106,
        "Cores:   " + String(chip.cores) +
        "  |  " + String(ESP.getCpuFreqMHz()) + " MHz",
        UI_MAIN, 1);

    drawStringCustom(20, 118,
        "Flash:   " + formatMB(ESP.getFlashChipSize()),
        UI_MAIN, 1);

    drawStringCustom(20, 130,
        "MAC WiFi: " + formatMAC(macWifi),
        UI_MAIN, 1);

    drawStringCustom(20, 142,
        "MAC BT:   " + formatMAC(macBT),
        UI_MAIN, 1);
}

// Redesenha apenas os valores dinâmicos (chamado periodicamente)
static void drawDynamicInfo(unsigned long sessionStartMs) {
    // Valores a exibir
    unsigned long uptimeMs   = millis() - sessionStartMs;
    unsigned long bootCount  = nvsGetULong("boot_cnt", 0);
    uint32_t heapFree        = ESP.getFreeHeap();
    uint32_t heapTotal       = ESP.getHeapSize();
    float    tempC           = readChipTemperatureC();

    // Sanear a temperatura (às vezes o sensor retorna valores absurdos no início)
    if (tempC < 0 || tempC > 125) tempC = 0;

    // Área dinâmica: y 170-212 (limpar antes de redesenhar)
    tft.fillRect(18, 170, 294, 44, TFT_BLACK);

    drawStringCustom(20, 170,
        "Boot #:   " + String(bootCount),
        UI_MAIN, 1);

    drawStringCustom(20, 182,
        "Uptime:   " + formatUptime(uptimeMs),
        UI_MAIN, 1);

    drawStringCustom(20, 194,
        "Heap:     " + formatKB(heapFree) + " / " + formatKB(heapTotal),
        UI_MAIN, 1);

    if (tempC > 0) {
        char tbuf[16];
        snprintf(tbuf, sizeof(tbuf), "%.1f C", tempC);
        drawStringCustom(20, 206, "Temp:     " + String(tbuf), UI_MAIN, 1);
    } else {
        drawStringCustom(20, 206, "Temp:     --", UI_ACCENT, 1);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  MAIN · SYSTEM INFO
// ═══════════════════════════════════════════════════════════════════════════
void runSystemInfo() {

    // Espera a liberação do OK do menu anterior
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);

    beep(1800, 30);

    unsigned long sessionStart = millis();
    drawStaticLayout();
    drawStaticInfo();
    drawDynamicInfo(sessionStart);

    unsigned long lastRefresh = millis();
    const unsigned long REFRESH_MS = 500;

    bool exitScreen = false;
    unsigned long okPressStart = 0;
    bool okHeld = false;

    while (!exitScreen) {
        // Refresh periódico dos valores dinâmicos
        if (millis() - lastRefresh > REFRESH_MS) {
            drawDynamicInfo(sessionStart);
            lastRefresh = millis();
        }

        // Detecta hold do OK (~300ms) para sair
        if (digitalRead(BTN_OK) == LOW) {
            if (!okHeld) {
                okPressStart = millis();
                okHeld = true;
            } else if (millis() - okPressStart > 300) {
                exitScreen = true;
            }
        } else {
            okHeld = false;
        }

        delay(10);
    }

    beep(1400, 30);
    delay(20);
    beep(1800, 40);

    // Espera a liberação
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);
}