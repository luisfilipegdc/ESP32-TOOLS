#include "Storage.h"
#include "Pins.h"

#if SD_ENABLED

#include <SPI.h>
#include <SD.h>

static bool g_mounted = false;

bool storageBegin() {
    // Reusa o mesmo barramento SPI do NRF24 (VSPI: SCK/MISO/MOSI).
    // Chamar SPI.begin() de novo é seguro (o NRF também chama).
    SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN);
    g_mounted = SD.begin(SD_CS_PIN);
    return g_mounted;
}

bool storageAvailable() {
    return g_mounted;
}

bool storageAppendLine(const char* path, const String& line) {
    if (!g_mounted) return false;
    File f = SD.open(path, FILE_APPEND);
    if (!f) return false;
    f.println(line);
    f.close();
    return true;
}

uint32_t storageFreeMB() {
    if (!g_mounted) return 0;
    uint64_t freeBytes = SD.totalBytes() - SD.usedBytes();
    return (uint32_t)(freeBytes / (1024ULL * 1024ULL));
}

#else   // SD_ENABLED == 0 → stubs neutros

bool     storageBegin()                                { return false; }
bool     storageAvailable()                            { return false; }
bool     storageAppendLine(const char*, const String&) { return false; }
uint32_t storageFreeMB()                               { return 0;     }

#endif
