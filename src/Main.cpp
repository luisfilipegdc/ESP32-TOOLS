#include <Arduino.h>
#include <TFT_eSPI.h>
#include "PepeDraw.h"
#include "MenuSystem.h"
#include "Pins.h"
#include "Settings.h"
#include "NVSStore.h"
#include "SplashScreen.h"

// ═══════════════════════════════════════════════════════════════════════════
//  ESP32-TOOLS · Firmware principal
//  O main.cpp apenas inicializa o hardware e entrega o controle ao menu.
// ═══════════════════════════════════════════════════════════════════════════

TFT_eSPI tft = TFT_eSPI();

// ── Carrega todas as preferências do NVS para as variáveis globais ──────
static void loadPreferences() {
    soundEnabled = nvsGetBool("sound_on",  true);
    soundVolume  = nvsGetInt ("sound_vol", 3);
    if (soundVolume < 1) soundVolume = 1;
    if (soundVolume > 5) soundVolume = 5;
}

// ── Incrementa o contador de boots (útil para o System Info depois) ─────
static void bumpBootCount() {
    unsigned long bc = nvsGetULong("boot_cnt", 0);
    bc++;
    nvsSetULong("boot_cnt", bc);
    Serial.printf("[NVS] Boot count: %lu\n", bc);
}

void setup() {
    Serial.begin(115200);

    // ── Botões ──────────────────────────────────────────────────────────
    pinMode(BTN_UP,   INPUT_PULLUP);
    pinMode(BTN_OK,   INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);

    // ── Buzzer ──────────────────────────────────────────────────────────
    ledcSetup(0, 2000, 8);
    ledcAttachPin(BUZZER_PIN, 0);
    ledcWriteTone(0, 0);

    // ── NVS: carregar configuração salva ────────────────────────────────
    nvsBegin();
    loadPreferences();
    bumpBootCount();

    // ── Reset da tela ───────────────────────────────────────────────────
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);  delay(100);
    digitalWrite(4, HIGH); delay(100);

    tft.begin();
    tft.setRotation(1);

    tft.fillScreen(TFT_BLACK);


    tft.begin();
    tft.setRotation(1);

    tft.fillScreen(TFT_BLACK);

    // ── Splash screen (espera o usuário pressionar OK) ──────────────────
    runSplashScreen();

    // ── Menu principal (loop infinito, nunca retorna) ───────────────────
    runMainMenu();

    // ── Menu principal (loop infinito, nunca retorna) ───────────────────
    runMainMenu();
}

void loop() {
    delay(1000);
}