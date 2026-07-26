#include "BLEScanner.h"
#include <TFT_eSPI.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include "PepeDraw.h"
#include "Pins.h"
#include "SoundUtils.h"

extern TFT_eSPI tft;

// ═══════════════════════════════════════════════════════════════════════════
//  CONFIGURAÇÃO
// ═══════════════════════════════════════════════════════════════════════════
#define MAX_DEVICES     30      // tope de dispositivos mostrados
#define SCAN_TIME_S     3       // segundos por ciclo de scan (luego itera)
#define VISIBLE_ROWS    6       // filas visibles en la lista

// ═══════════════════════════════════════════════════════════════════════════
//  ESTRUTURA DE DISPOSITIVO
// ═══════════════════════════════════════════════════════════════════════════
struct BLEDev {
    String   name;
    String   mac;
    int      rssi;
    int      addrType;
    bool     hasManufData;
    uint16_t vendorId;      // primeros 2 bytes de manufacturer data
    String   manufHex;      // manufacturer data en hex (máx 16 bytes mostrados)
    int      serviceCount;
    String   serviceSummary; // nome do primeiro serviço ou "Services: N"
};

static BLEDev devices[MAX_DEVICES];
static int deviceCount = 0;

// ═══════════════════════════════════════════════════════════════════════════
//  VENDOR LOOKUP · pelos primeiros 2 bytes do manufacturer data (Company ID)
//  Lista oficial Bluetooth SIG. Os mais comuns.
// ═══════════════════════════════════════════════════════════════════════════
static const char* bleVendorName(uint16_t id) {
    switch (id) {
        case 0x004C: return "Apple";
        case 0x0075: return "Samsung";
        case 0x0006: return "Microsoft";
        case 0x00E0: return "Google";
        case 0x038F: return "Xiaomi";
        case 0x02E1: return "Amazon";
        case 0x0157: return "Fitbit";
        case 0x0059: return "Nordic";
        case 0x0499: return "Ruuvi";
        case 0x0131: return "Huawei";
        case 0x0001: return "Ericsson";
        case 0x000F: return "Broadcom";
        case 0x000D: return "Texas Instr";
        case 0x004F: return "Nokia";
        case 0x0087: return "Garmin";
        case 0x012D: return "Sony";
        case 0x0505: return "Bose";
        case 0x01DA: return "Logitech";
        case 0x0154: return "Withings";
        case 0x000A: return "Canon";
        case 0x0046: return "Marvell";
        case 0x022B: return "Tile";
        case 0x0310: return "SGL Italia";
        default:     return nullptr;
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  HELPERS
// ═══════════════════════════════════════════════════════════════════════════

// Categoriza o RSSI numa descrição humana
static const char* rssiLabel(int rssi) {
    if (rssi >= -50) return "VERY CLOSE";
    if (rssi >= -65) return "CLOSE";
    if (rssi >= -80) return "NEAR";
    return "FAR";
}

// Converte o RSSI em 4 barras de sinal
static int rssiBars(int rssi) {
    if (rssi >= -55) return 4;
    if (rssi >= -70) return 3;
    if (rssi >= -85) return 2;
    if (rssi >= -95) return 1;
    return 0;
}

// Formatea manufacturer data en hex (primeros N bytes)
static String formatHex(const uint8_t* data, size_t len, size_t maxBytes) {
    String out = "";
    size_t show = len < maxBytes ? len : maxBytes;
    for (size_t i = 0; i < show; i++) {
        char buf[4];
        snprintf(buf, sizeof(buf), "%02X ", data[i]);
        out += buf;
    }
    if (len > maxBytes) out += "...";
    return out;
}

// Tipo de endereço BLE → string
static const char* addrTypeLabel(int t) {
    switch (t) {
        case 0:  return "Public";
        case 1:  return "Random";
        case 2:  return "Public-ID";
        case 3:  return "Random-ID";
        default: return "Unknown";
    }
}

// Verifica se uma MAC já está na lista. Retorna o índice ou -1.
static int findDevice(const String& mac) {
    for (int i = 0; i < deviceCount; i++) {
        if (devices[i].mac == mac) return i;
    }
    return -1;
}

// Insere ou atualiza um dispositivo
static void upsertDevice(BLEAdvertisedDevice& ad) {
    String mac = String(ad.getAddress().toString().c_str());
    String name = ad.haveName() ? String(ad.getName().c_str()) : "";

    int idx = findDevice(mac);
    bool isNew = (idx < 0);

    if (isNew) {
        if (deviceCount >= MAX_DEVICES) return;
        idx = deviceCount++;
    }

    BLEDev& d = devices[idx];
    d.mac  = mac;
    d.rssi = ad.getRSSI();
    d.addrType = (int)ad.getAddressType();

    // Salva o nome só se veio (dispositivos BLE às vezes anunciam sem nome)
    if (name.length() > 0) d.name = name;
    else if (d.name.length() == 0) d.name = "";

    // Servicios
    d.serviceCount = ad.getServiceUUIDCount();
    if (d.serviceCount > 0) {
        d.serviceSummary = String(d.serviceCount) + " service" +
                           (d.serviceCount > 1 ? "s" : "");
    } else {
        d.serviceSummary = "No services";
    }

    // Manufacturer data
    d.hasManufData = ad.haveManufacturerData();
    if (d.hasManufData) {
        std::string md = ad.getManufacturerData();
        if (md.size() >= 2) {
            d.vendorId = ((uint16_t)(uint8_t)md[1] << 8) | (uint8_t)md[0];
            d.manufHex = formatHex((const uint8_t*)md.data(), md.size(), 12);
        } else {
            d.vendorId = 0;
            d.manufHex = "";
        }
    } else {
        d.vendorId = 0;
        d.manufHex = "";
    }

    // Beep sutil quando encontramos um dispositivo novo
    if (isNew) beep(2200, 20);
}

// Ordena por RSSI descendente (os mais próximos primeiro)
static void sortDevices() {
    // Bubble sort — deviceCount é no máx 30, é suficiente
    for (int i = 0; i < deviceCount - 1; i++) {
        for (int j = 0; j < deviceCount - 1 - i; j++) {
            if (devices[j].rssi < devices[j + 1].rssi) {
                BLEDev tmp = devices[j];
                devices[j] = devices[j + 1];
                devices[j + 1] = tmp;
            }
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  CALLBACK DE SCAN
// ═══════════════════════════════════════════════════════════════════════════
class BLEScanCallback : public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice ad) override {
        upsertDevice(ad);
    }
};

// ═══════════════════════════════════════════════════════════════════════════
//  DESENHO · LISTA PRINCIPAL
// ═══════════════════════════════════════════════════════════════════════════
static void drawListFrame() {
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(0, 0, 320, 240, UI_MAIN);

    // Header
    drawStringBig(10, 8, "BLE SCAN", UI_MAIN, 1);
    tft.drawFastHLine(0, 30, 320, UI_ACCENT);

    // Footer
    tft.drawFastHLine(0, 215, 320, UI_ACCENT);
    drawStringCustom(10, 222, "UP/DN:NAV  OK:DETAILS  OK-HOLD:EXIT",
                     UI_ACCENT, 1);
}

// Desenha a lista de dispositivos + contador
static void drawList(int cursor, int scrollOffset, int totalSeen) {
    // Limpa a área do contador (sem redesenhar todo o header)
    tft.fillRect(140, 8, 175, 16, TFT_BLACK);

    // Contador "FOUND: N"
    String hdr = "FOUND: " + String(deviceCount);
    drawStringCustom(150, 12, hdr, UI_SELECT, 1);

    // Indicador "SCANNING..." parpadeante
    if ((millis() / 500) % 2) {
        drawStringCustom(235, 12, "SCANNING", UI_ACCENT, 1);
    } else {
        tft.fillRect(235, 10, 75, 10, TFT_BLACK);
    }

    // Área da lista (y=36 a y=212)
    tft.fillRect(1, 33, 318, 180, TFT_BLACK);

    if (deviceCount == 0) {
        drawStringCustom(70, 110, "Searching devices...", UI_ACCENT, 1);
        return;
    }

    const int rowHeight = 28;
    const int listY = 36;

    for (int i = 0; i < VISIBLE_ROWS; i++) {
        int idx = i + scrollOffset;
        if (idx >= deviceCount) break;

        int y = listY + i * rowHeight;
        bool selected = (idx == cursor);

        if (selected) {
            tft.fillRect(5, y, 310, rowHeight - 2, UI_SELECT);
        }

        uint16_t colMain = selected ? UI_BG : UI_MAIN;
        uint16_t colSub  = selected ? UI_BG : UI_ACCENT;

        BLEDev& d = devices[idx];

        // Nome (ou "<unnamed>")
        String displayName = d.name.length() > 0 ? d.name : "<unnamed>";
        if (displayName.length() > 20) {
            displayName = displayName.substring(0, 18) + "..";
        }
        drawStringCustom(10, y + 4, displayName, colMain, 2);

        // MAC (abaixo, menor)
        drawStringCustom(10, y + 18, d.mac, colSub, 1);

        // RSSI + barras à direita
        String rssiStr = String(d.rssi) + "dBm";
        drawStringCustom(210, y + 4, rssiStr, colMain, 2);

        // Barras de sinal
        int bars = rssiBars(d.rssi);
        int bx = 280, by = 20;
        for (int b = 0; b < 4; b++) {
            int bh = 3 + b * 2;
            uint16_t c = (b < bars)
                ? (selected ? UI_BG : (bars >= 3 ? TFT_GREEN :
                                       bars >= 2 ? TFT_YELLOW : TFT_ORANGE))
                : (selected ? UI_BG : UI_ACCENT);
            if (b < bars) {
                tft.fillRect(bx + b*5, by - bh, 3, bh, c);
            } else {
                tft.drawRect(bx + b*5, by - bh, 3, bh, c);
            }
        }
    }

    // Barra de rolagem lateral se houver mais que VISIBLE_ROWS
    if (deviceCount > VISIBLE_ROWS) {
        int total = deviceCount;
        int barH = (VISIBLE_ROWS * 176) / total;
        int barY = 36 + (scrollOffset * (176 - barH)) / (total - VISIBLE_ROWS);
        tft.fillRect(314, barY, 4, barH, UI_ACCENT);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
//  DESENHO · TELA DE DETALHES
// ═══════════════════════════════════════════════════════════════════════════
static void drawDetails(const BLEDev& d) {
    tft.fillScreen(TFT_BLACK);
    tft.drawRect(0, 0, 320, 240, UI_MAIN);

    // Header
    drawStringBig(10, 8, "DEVICE DETAILS", UI_MAIN, 1);
    tft.drawFastHLine(0, 30, 320, UI_ACCENT);

    int y = 40;
    const int lineH = 14;

    // Nombre
    String name = d.name.length() > 0 ? d.name : "<unnamed>";
    drawStringCustom(10, y, "Name:    " + name, UI_MAIN, 1);
    y += lineH;

    // MAC
    drawStringCustom(10, y, "MAC:     " + d.mac, UI_MAIN, 1);
    y += lineH;

    // RSSI com categoria
    String rssiLine = "RSSI:    " + String(d.rssi) + " dBm  (" +
                      String(rssiLabel(d.rssi)) + ")";
    drawStringCustom(10, y, rssiLine, UI_MAIN, 1);
    y += lineH;

    // Tipo de endereço
    drawStringCustom(10, y, "AddrType: " + String(addrTypeLabel(d.addrType)),
                     UI_MAIN, 1);
    y += lineH;

    // Vendor (se conseguimos identificar)
    const char* vendor = nullptr;
    if (d.hasManufData && d.vendorId != 0) {
        vendor = bleVendorName(d.vendorId);
    }
    String vendorStr;
    if (vendor) {
        vendorStr = "Vendor:  " + String(vendor);
    } else if (d.hasManufData && d.vendorId != 0) {
        char buf[16];
        snprintf(buf, sizeof(buf), "0x%04X", d.vendorId);
        vendorStr = "Vendor:  " + String(buf) + " (unknown)";
    } else {
        vendorStr = "Vendor:  --";
    }
    drawStringCustom(10, y, vendorStr, UI_SELECT, 1);
    y += lineH + 4;

    // Services
    tft.drawFastHLine(10, y, 300, UI_ACCENT);
    y += 4;
    drawStringCustom(10, y, "Services: " + String(d.serviceCount), UI_MAIN, 1);
    y += lineH;

    if (d.serviceCount > 0) {
        drawStringCustom(20, y, d.serviceSummary, UI_ACCENT, 1);
        y += lineH;
    } else {
        drawStringCustom(20, y, "(none advertised)", UI_ACCENT, 1);
        y += lineH;
    }

    y += 4;
    tft.drawFastHLine(10, y, 300, UI_ACCENT);
    y += 4;

    // Manufacturer data
    if (d.hasManufData) {
        drawStringCustom(10, y, "Mfg data:", UI_MAIN, 1);
        y += lineH;
        drawStringCustom(20, y, d.manufHex, UI_ACCENT, 1);
        y += lineH;
    } else {
        drawStringCustom(10, y, "Mfg data: --", UI_MAIN, 1);
        y += lineH;
    }

    // Footer
    tft.drawFastHLine(0, 215, 320, UI_ACCENT);
    drawStringCustom(10, 222, "OK: RETURN TO LIST", UI_ACCENT, 1);
}

// ═══════════════════════════════════════════════════════════════════════════
//  MAIN · BLE SCANNER
// ═══════════════════════════════════════════════════════════════════════════
void runBLEScanner() {

    // Espera soltar o OK do menu anterior
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);

    // Reset estado
    deviceCount = 0;
    int cursor = 0;
    int scrollOffset = 0;

    // Tela inicial
    drawListFrame();
    drawList(cursor, scrollOffset, 0);

    // Beep de arranque
    beep(1500, 40);
    delay(20);
    beep(2100, 60);

    // Inicializa o BLE
    BLEDevice::init("");
    BLEScan* scanner = BLEDevice::getScan();
    scanner->setAdvertisedDeviceCallbacks(new BLEScanCallback(), false);
    scanner->setActiveScan(true);    // pide scan response (más info)
    scanner->setInterval(100);
    scanner->setWindow(99);

    bool exitScreen = false;
    bool inDetails = false;
    int detailsIdx = 0;

    unsigned long lastScanStart = 0;
    unsigned long lastRedraw = 0;
    unsigned long okPressStart = 0;
    bool okHeld = false;

    // Inicia o primeiro scan assíncrono
    scanner->start(SCAN_TIME_S, nullptr, false);
    lastScanStart = millis();

    while (!exitScreen) {

        // Reinicia o scan periodicamente (contínuo)
        if (millis() - lastScanStart > (SCAN_TIME_S * 1000UL + 200)) {
            scanner->clearResults();   // libera memoria del ciclo anterior
            scanner->start(SCAN_TIME_S, nullptr, false);
            lastScanStart = millis();
            sortDevices();
            // Garante que o cursor siga válido após reordenar
            if (cursor >= deviceCount && deviceCount > 0) cursor = deviceCount - 1;
        }

        // Redraw periódico se estamos na lista (cada 400 ms)
        if (!inDetails && millis() - lastRedraw > 400) {
            drawList(cursor, scrollOffset, deviceCount);
            lastRedraw = millis();
        }

        // ── Controles no modo LISTA ────────────────────────────────────
        if (!inDetails) {

            // UP
            if (digitalRead(BTN_UP) == LOW) {
                if (deviceCount > 0) {
                    cursor = (cursor - 1 + deviceCount) % deviceCount;
                    if (cursor < scrollOffset) scrollOffset = cursor;
                    if (cursor >= scrollOffset + VISIBLE_ROWS)
                        scrollOffset = cursor - VISIBLE_ROWS + 1;
                    beep(2200, 20);
                    drawList(cursor, scrollOffset, deviceCount);
                    lastRedraw = millis();
                }
                delay(180);
            }

            // DOWN
            if (digitalRead(BTN_DOWN) == LOW) {
                if (deviceCount > 0) {
                    cursor = (cursor + 1) % deviceCount;
                    if (cursor < scrollOffset) scrollOffset = cursor;
                    if (cursor >= scrollOffset + VISIBLE_ROWS)
                        scrollOffset = cursor - VISIBLE_ROWS + 1;
                    beep(2200, 20);
                    drawList(cursor, scrollOffset, deviceCount);
                    lastRedraw = millis();
                }
                delay(180);
            }

            // OK: press curto = entrar nos detalhes; press longo = sair
            if (digitalRead(BTN_OK) == LOW) {
                if (!okHeld) {
                    okPressStart = millis();
                    okHeld = true;
                } else if (millis() - okPressStart > 400) {
                    // HOLD: sair
                    exitScreen = true;
                }
            } else {
                if (okHeld && deviceCount > 0) {
                    // Fue press corto: entrar a detalles
                    detailsIdx = cursor;
                    inDetails = true;
                    beep(1800, 40);
                    drawDetails(devices[detailsIdx]);
                }
                okHeld = false;
            }

        // ── Controles no modo DETAILS ──────────────────────────────────
        } else {
            // Qualquer OK volta à lista
            if (digitalRead(BTN_OK) == LOW) {
                delay(200);
                while (digitalRead(BTN_OK) == LOW) delay(5);
                beep(1400, 40);
                inDetails = false;
                drawListFrame();
                drawList(cursor, scrollOffset, deviceCount);
                lastRedraw = millis();
            }
        }

        delay(10);
    }

    // Cleanup
    scanner->stop();
    scanner->clearResults();
    BLEDevice::deinit(false);

    beep(1800, 40);
    delay(20);
    beep(1200, 60);

    // Espera a liberação
    while (digitalRead(BTN_OK) == LOW) delay(5);
    delay(100);
}