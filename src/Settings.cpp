#include "Settings.h"

// ═══════════════════════════════════════════════════════════════════════════
//  Variáveis globais de configuração do usuário.
//
//  IMPORTANTE: estes valores "iniciais" são apenas fallback.
//  O valor real é carregado do NVS em setup() via loadSettings().
//  Qualquer mudança em runtime deve ser salva com saveSettings().
// ═══════════════════════════════════════════════════════════════════════════

bool soundEnabled = true;
int  soundVolume  = 3;   // faixa 1-5