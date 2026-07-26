<div align="center">

# 🦎 ESP32-TOOLS

### Firmware multiferramenta de segurança WiFi + Bluetooth para ESP32

*Inspirado no Flipper Zero, Bruce e ESP32 Marauder — feito do zero no México*

<img src="img/splash.jpg" width="400" alt="Tela de splash com o axolote"/>

**By PepeAngell** · [Instagram](https://instagram.com/esp32_tools) · [Facebook](https://www.facebook.com/esp32tools/) · [GitHub](https://github.com/pepeangell5)

![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform: ESP32](https://img.shields.io/badge/platform-ESP32-red.svg)
![Framework: Arduino](https://img.shields.io/badge/framework-Arduino-00979D.svg)
![Built with: PlatformIO](https://img.shields.io/badge/built%20with-PlatformIO-orange.svg)
![Version: 2.0](https://img.shields.io/badge/version-2.0-brightgreen.svg)
[![Web Installer](https://img.shields.io/badge/⚡_FLASH_FROM_BROWSER-fa4500?style=for-the-badge)](https://pepeangell5.github.io/ESP32-TOOLS/)
</div>

---

## 🎬 Demo ao vivo

<div align="center">
<img src="img/ESP32.gif" width="500" alt="Demo do firmware navegando por todas as ferramentas"/>

*Passeio completo pelos menus e ferramentas do firmware*

</div>

---

## 🆕 Novidades na versão 2.0

A v2.0 expande massivamente o firmware com **6 ferramentas novas**, um **sistema completo de configuração WiFi** com teclado virtual, e vários extras de qualidade de vida:

- 🌐 **Evil Portal** — portal cativo com AP falso, DNS spoofing e captura de credenciais (modo SIMPLE + modo CLONE+Deauth)
- 🎭 **KARMA Attack** — captura probes e os anuncia como redes existentes para atrair dispositivos
- 📡 **Probe Request Sniffer** — descobre as redes que os celulares próximos estão procurando
- 🌤️ **Clock & Weather** — relógio NTP + clima ao vivo com detecção de localização por IP
- ⌨️ **Teclado Virtual QWERTY** — entrada de texto reutilizável com ñ e símbolos
- 🌙 **Screensaver** — o axolote quicando estilo logo do DVD, com estrelinhas
- 🔧 **WiFi Config persistente** — escreva sua rede uma única vez, fica salva
- 🗑️ **Forget WiFi** — opção em Settings para esquecer a rede salva

---

## 📖 O que é o ESP32-TOOLS?

**ESP32-TOOLS** é um firmware completo para uma multiferramenta portátil baseada em ESP32, projetada para testes de segurança WiFi e Bluetooth. Inclui scanner de redes, analisador de espectro, monitor de pacotes, gerador de beacons, deauther, disruptor Bluetooth, evil portal, KARMA attack, relógio com clima ao vivo e mais — tudo com uma interface própria estilo console retrô e nosso mascote oficial: um axolote de óculos escuros. 😎

Inspirado em projetos como **Flipper Zero**, **ESP32 Marauder** e **Bruce**, mas construído do zero com personalidade própria, em espanhol, e pensado para a comunidade maker de língua hispânica.

---

## ⚠️ Aviso legal

Esta ferramenta foi pensada com fins **educativos e de pentest em redes próprias ou com autorização explícita**. Várias de suas funções (Deauther, BT Disruptor, Beacon Spam, Evil Portal, KARMA) podem causar interferência em redes de terceiros ou capturar informações alheias.

**No México e na maioria dos países, o uso destas ferramentas contra redes ou dispositivos alheios sem consentimento constitui crime federal** (Art. 211 bis do Código Penal Federal no México; no Brasil, veja a Lei nº 12.737/2012 — "Lei Carolina Dieckmann" — e o Marco Civil da Internet). O autor não se responsabiliza pelo mau uso do firmware. Você é 100% responsável por como o utiliza.

Use com a cabeça. 🧠

---

## 🛠️ Ferramentas incluídas

<div align="center">

| Categoria | Ferramentas |
|:---|:---|
| 📡 **WiFi** | WiFi Scanner · Beacon Spam · Deauther · **Evil Portal** 🆕 · **Probe Sniffer** 🆕 · **KARMA Attack** 🆕 |
| 🔵 **Bluetooth** | BLE Scanner · BLE Spam · BT Disruptor |
| 📻 **Rádio 2.4GHz** | Jammer · Spectrum Analyzer (3 modos) |
| 📊 **Monitoramento** | Packet Monitor |
| ⚙️ **Sistema** | Settings (com Forget WiFi 🆕) · System Info · **Clock & Weather** 🆕 |

</div>

**14 ferramentas funcionais** + sistema completo com splash, screensaver, persistência NVS, e módulos reutilizáveis (teclado virtual, WiFi config).

---

## 📸 Galeria

### Menu principal estilo carrossel

<div align="center">
<img src="img/menu.jpg" width="45%" alt="WIFI TOOLS"/>
<img src="img/menu2.jpg" width="45%" alt="RADIO TOOLS"/>
</div>

Navegação vertical tipo Flipper, com ícones pixel art 64x64 para cada categoria. Animação slide suave, flash de OK com beeps, e 5 categorias: **WiFi · Radio · Bluetooth · Monitor · System**.

### Screensaver

<div align="center">
<img src="img/screensaver.jpg" width="50%" alt="Screensaver com o axolote quicando"/>
</div>

Após 30 segundos sem atividade, entra o screensaver: o axolote quica estilo logo do DVD, com estrelinhas piscando ao fundo, textos rotativos ("ESP32-TOOLS", "by PepeAngell", "ZzZ...") e contador de uptime. Qualquer botão o acorda.

---

### 📡 WiFi Tools

<div align="center">
<img src="img/wifiscanner.jpg" width="45%" alt="WiFi Scanner"/>
<img src="img/wifitools.jpg" width="45%" alt="Submenu WiFi Tools"/>
</div>

**WiFi Scanner** — descobre todas as redes 2.4GHz próximas com SSID, canal, RSSI, tipo de encriptação (WEP/WPA2/WPA3 com cores), detecção de redes ocultas e consulta de fabricantes mexicanos (Telmex, Totalplay, Izzi, Megacable, AT&T, etc.) por OUI.

**Beacon Spam** — transmite centenas de redes WiFi fictícias com channel hopping (CH 1→6→11) e rotação de BSSID. 5 modos temáticos:

<div align="center">
<img src="img/beaconspam.jpg" width="45%" alt="Menu do Beacon Spam"/>
<img src="img/beaconspam2.jpg" width="45%" alt="Beacon Spam ativo"/>
</div>

- 🌶️ **Mexipicante** — 40 SSIDs picantes em espanhol
- 🎭 **Memes Clássicos** — FBI_Van, Virus.exe, etc.
- 😱 **Paranoia** — "Camara_Oculta_Activa", "Te_Estamos_Grabando"...
- 💀 **Chaos UTF-8** — só emojis e símbolos
- 🎪 **Mix Total** — todos combinados (~100 SSIDs únicos)

Taxa de transmissão: ~190 beacons/seg.

**Deauther** — desconecta dispositivos de redes WiFi usando deauth frames 802.11.

<div align="center">
<img src="img/deautheralert.jpg" width="45%" alt="Aviso do Deauther"/>
<img src="img/deauther.jpg" width="45%" alt="Menu de ação do Deauther"/>
</div>

- Scan de APs com seleção visual
- Scan de clientes conectados (modo promíscuo)
- Ataque dirigido a um cliente específico ou broadcast ao AP inteiro
- **Rambo Mode**: ataque simultâneo a todas as APs com channel hopping
- Requer patch do SDK (instruções na seção de instalação)

---

### 🆕 Evil Portal

<div align="center">
<img src="img/evilportal_modes.jpg" width="45%" alt="Modos do Evil Portal"/>
<img src="img/evilportal.jpg" width="45%" alt="Menu principal do Evil Portal"/>
</div>

Portal cativo completo com AP falso + DNS spoofing + servidor HTTP. Quando um dispositivo se conecta ao AP do ESP32, todas as URLs são redirecionadas para uma página de "login" que se parece com Facebook, Google, Instagram ou TikTok.

**2 modos disponíveis:**

- 🟢 **Modo SIMPLE** — AP fixo com um de 10 SSIDs predefinidos (`INFINITUM_5G_LIBRE`, `TOTALPLAY_INVITADOS`, `Starbucks_Clientes`, `OXXO_WiFi_Gratis`, etc.). Ideal para demos.
- 🔴 **Modo CLONE + Deauth** — escaneia a rede real, **clona seu SSID e canal**, e simultaneamente dispara ataques deauth contra a rede original para forçar os clientes a reconectar ao clone.

**4 plataformas de phishing:**
- 📘 Facebook com SVG circular oficial
- 🟢 Google com logo colorido
- 📸 Instagram com gradiente + ícone de câmera
- 🎵 TikTok com logo ciano/magenta

Depois de capturar credenciais, redireciona para `/success`, que rebota para `google.com` para não levantar suspeitas.

#### Logs persistentes

<div align="center">
<img src="img/evilportal_logs.jpg" width="50%" alt="Logs capturados"/>
</div>

Os logs são salvos em NVS (até 20, FIFO circular) e persistem ao reiniciar. Mostra plataforma, email/usuário e senha capturados. Apagável pelo menu com confirmação.

---

### 🆕 Probe Request Sniffer

<div align="center">
<img src="img/probesniffer.jpg" width="50%" alt="Probe Sniffer"/>
</div>

Modo promíscuo que captura **probe requests** — os pacotes que os celulares enviam perguntando "essa rede salva está por perto?". Útil para descobrir padrões de mobilidade e combinar com o KARMA.

- Channel hopping 1→6→11 a cada 2 segundos
- Deduplica por SSID, mostra contador de vezes visto, RSSI e "há quanto tempo" foi visto
- Clique curto no OK = ordenar por contagem
- OK pressionado = sair
- Até 50 SSIDs únicos em memória

---

### 🆕 KARMA Attack

<div align="center">
<img src="img/karma.jpg" width="45%" alt="KARMA Fase 1"/>
<img src="img/karma2.jpg" width="45%" alt="KARMA Fase 2 ativo"/>
</div>

O ataque mais sofisticado do firmware. Combina Probe Sniffer + Beacon Spam de forma cirúrgica:

1. **Fase 1** (15s) — escuta quais redes os celulares próximos estão procurando
2. **Fase 2** — transmite beacons falsificando esses SSIDs como redes abertas existentes

Dispositivos vulneráveis (Android antigos, IoT, smart TVs, câmeras) que tinham essas redes salvas como abertas se conectam automaticamente. Combinado depois com o Evil Portal, vira um ataque completo de phishing.

**Eficácia real:** ~30-50% em uma multidão (iOS 14+ e Android 10+ resistem ao KARMA por randomização de MAC). Suficiente para demonstrar o ataque e entender o risco.

---

### 🔵 Bluetooth Tools

<div align="center">
<img src="img/blescan.jpg" width="50%" alt="BLE Scanner"/>
</div>

**BLE Scanner** — descobre dispositivos Bluetooth Low Energy próximos (AirPods, smartwatches, beacons, tags, etc.). Lista ordenada por RSSI com barras de sinal, consulta de fabricante por OUI (Apple, Samsung, Xiaomi, Microsoft, Google, e ~20 mais), tela de detalhes com MAC, serviços anunciados e manufacturer data em hex.

**BLE Spam** — transmite advertisements BLE falsos que disparam pop-ups de pareamento em dispositivos próximos. 5 protocolos implementados:

- 🍎 **Apple Continuity** — pop-ups de AirPods Pro, AirPods Max, Beats, Apple TV (13 modelos)
- 📱 **Samsung Easy Setup** — Galaxy Buds Pro, Buds 2, Buds FE (7 modelos)
- 🪟 **Microsoft Swift Pair** — teclados, mouse Surface, controle de Xbox
- 🟢 **Google Fast Pair** — Pixel Buds, dispositivos Nest
- 🌪️ **CHAOS Mode** — rotaciona os 4 protocolos aleatoriamente

**BT Disruptor** — ataque dirigido a um dispositivo BLE específico. Após escanear e selecionar o alvo, gera connection flood, L2CAP ping storm, spoof de identidade ou chaos combinado. Útil para degradar a conexão de fones/caixas de som BLE.

---

### 📻 Radio Tools

<div align="center">
<img src="img/spectrum.jpg" width="32%" alt="Spectrum"/>
<img src="img/spectrum2.jpg" width="32%" alt="Waterfall"/>
<img src="img/sprectrum3.jpg" width="32%" alt="WiFi Chans"/>
</div>

**Radio Scanner** com NRF24L01 — analisador de espectro 2.4GHz com 3 modos:

- **SPECTRUM** — 80 barras com gradiente vertical, peak hold, som geiger
- **WATERFALL** — 166 linhas de histórico temporal com mapa de cores
- **WIFI CHANS** — 13 barras (uma por canal WiFi), recomendação do melhor canal

**Radio Jammer** — transmissão contínua em 2.4GHz com o NRF24. 3 modos: Turbo (concentrado), Wide (±2 canais), Varredura (os 14 canais WiFi). *Nota: o jamming é ilegal no México e no Brasil fora de contextos educativos isolados.*

---

### 📊 Packet Monitor

<div align="center">
<img src="img/packetmonitor.jpg" width="50%" alt="Packet Monitor"/>
</div>

Sniffer promíscuo de pacotes 802.11 por canal. Mostra PPS (pacotes por segundo) com código de cores, VU meter vertical, gráfico histórico de 60 segundos e estatísticas acumuladas. 6 níveis de atividade (QUIET → LOW → ACTIVE → BUSY → HEAVY → FLOODED) com sons ambientes distintos por nível.

---

### 🆕 Clock & Weather

<div align="center">
<img src="img/clockweather.jpg" width="45%" alt="Submenu Clock & Weather"/>
<img src="img/clockweather2.jpg" width="45%" alt="Carregando clima"/>
</div>

<div align="center">
<img src="img/clockweather3.jpg" width="60%" alt="Tela principal do Clock & Weather"/>
</div>

Widget completo com NTP + geolocalização por IP + clima ao vivo:

- ⏰ **Hora grande em formato 12h** com AM/PM (ciano de manhã, laranja à tarde/noite)
- 📅 **Data em espanhol** ("Sábado, 25 de Abril")
- 🌡️ **Temperatura atual + sensação térmica** com código de cores
- 🌤️ **Ícones de clima em pixel art** (sol, nuvem, chuva, tempestade, neve, névoa)
- 💨 **Umidade e velocidade do vento**
- 🌅 **Horário do nascer e do pôr do sol**
- 🏙️ **Cidade detectada por IP** (sem necessidade de GPS)

**APIs gratuitas sem cadastro:**
- [ip-api.com](https://ip-api.com) para geolocalização por IP
- [Open-Meteo](https://open-meteo.com) para dados climáticos

**Tratamento correto de timezones:** mapper IANA → POSIX para que a hora seja exata em cada fuso horário, incluindo zonas sem horário de verão (Sinaloa, Sonora, Arizona) e com horário de verão (CDMX, EUA continental).

---

### 🆕 WiFi Config + Teclado Virtual

<div align="center">
<img src="img/keyboard.jpg" width="60%" alt="Teclado virtual digitando a senha"/>
</div>

Sistema reutilizável de configuração WiFi que qualquer ferramenta pode invocar:

- **Auto-conexão** silenciosa com credenciais salvas em NVS (5 segundos)
- **Scan automático** se não houver credenciais ou se a rede salva falhar
- **Seleção visual** de redes ordenadas por RSSI, com barras e tipo de encriptação
- **Teclado virtual QWERTY em espanhol** com ñ, símbolos com shift, toggle de maiúsculas, contador de caracteres e máscara de senha
- **Persistência NVS** — o usuário só escreve a rede **uma vez**

**Forget WiFi** disponível em `SYSTEM → Settings` para apagar as credenciais salvas, com confirmação de segurança (UI vermelha).

---

## 🔧 Hardware necessário

Lista de componentes para replicar este projeto. Tudo conseguível no México pela Amazon, Mercado Livre ou Steren por aproximadamente **$400-500 MXN** no total.

### Componentes principais

| Componente | Modelo específico | Função |
|:---|:---|:---|
| **Microcontrolador** | ESP32-D (ESP32-WROOM-32, 30 pinos) | Cérebro, WiFi + BT/BLE integrado |
| **Rádio 2.4GHz** | NRF24L01+ (com antena PCB integrada) | Analisador de espectro + jammer |
| **Tela** | TFT LCD Shield 2.4" ILI9341 (paralela 8-bit) | Display 320x240 |
| **Botões** | 3 × push buttons 12mm (estilo arcade) | Navegação: UP / OK / DOWN |
| **Buzzer** | Buzzer passivo 5V | Feedback de áudio |
| **Bateria** | LiPo 3.7V 1000mAh | Portabilidade |
| **Carga da bateria** | Módulo TP4056 com proteção | Carga por USB |
| **Conversor DC-DC** | Step-Up MT3608 ajustável a 5V | Alimenta ESP32 e tela |
| **Switch** | Interruptor deslizante de 2 posições | Liga/desliga |
| **PCB de prototipagem** | Placa perfurada 7x9cm (ou similar) | Montagem física |

### Opcional
- Cabos jumper dupont (fêmea-macho, macho-macho)
- Pin headers 2.54mm
- Case impresso em 3D (pendente para uma versão futura)

---

## 🔌 Diagrama de conexões

> 💡 Há também um **esquema visual de montagem** em [`docs/esquema_montagem.svg`](docs/esquema_montagem.svg) que consolida todas as ligações abaixo numa única imagem.

### ESP32 ↔ Tela TFT LCD Shield 2.4" (paralela 8-bit)

| Tela (Shield) | ESP32 (GPIO) | Função |
|:---|:---:|:---|
| D0 | 12 | Data bus bit 0 |
| D1 | 13 | Data bus bit 1 |
| D2 | 14 | Data bus bit 2 |
| D3 | 27 | Data bus bit 3 |
| D4 | 16 | Data bus bit 4 |
| D5 | 17 | Data bus bit 5 |
| D6 | 18 | Data bus bit 6 |
| D7 | 19 | Data bus bit 7 |
| RS / DC | 2 | Command/Data select |
| WR | 15 | Write control |
| CS | 5 | Chip Select |
| RST | 4 | Reset |
| RD | 3.3V | Read (fixo em alto) |
| VCC | 5V (do Step-Up) | Alimentação do backlight |
| GND | GND | Terra |

### ESP32 ↔ NRF24L01

| NRF24L01 | ESP32 (GPIO) | Função |
|:---|:---:|:---|
| CE | 21 | Chip Enable |
| CSN | 32 | Chip Select Not |
| SCK | 25 | SPI Clock |
| MISO | 26 | SPI Master In Slave Out |
| MOSI | 33 | SPI Master Out Slave In |
| VCC | 3.3V | ⚠️ Não conectar a 5V |
| GND | GND | Terra |

### Botões

| Botão | ESP32 (GPIO) | Resistor pull-up |
|:---|:---:|:---:|
| UP (cima) | 34 | ✅ Sim (externo) |
| OK (centro) | 35 | ✅ Sim (externo) |
| DOWN (baixo) | 23 | ❌ Usa pull-up interno |

> **Nota:** os GPIO 34 e 35 são somente-entrada no ESP32, por isso exigem pull-up externo (10kΩ a 3.3V). O GPIO 23 usa o pull-up interno do ESP32 (`INPUT_PULLUP`).

### Buzzer

| Buzzer | ESP32 |
|:---|:---:|
| Positivo (+) | GPIO 22 |
| Negativo (-) | GND |

### Alimentação

```
Bateria 3.7V 1000mAh ──► TP4056 (carga USB) ──► Switch ──► Step-Up MT3608 (ajustado a 5V) ──► ESP32 VIN + TFT VCC
                                                                                               │
                                                                                               └──► 3.3V regulado do ESP32 ──► NRF24 VCC
```

> ⚠️ **Importante:** o NRF24 **não tolera 5V**. Sempre alimente-o com os 3.3V do ESP32.

---

## 🚀 Instalação

Há duas formas de instalar o ESP32-TOOLS no seu hardware:

### ⚡ Opção 1 · Flasheio rápido pelo navegador (recomendado)

Se você só quer usar o firmware sem compilá-lo, pode flashear direto do navegador em menos de 1 minuto. **Não precisa instalar nada.**

🔗 **[https://pepeangell5.github.io/ESP32-TOOLS/](https://pepeangell5.github.io/ESP32-TOOLS/)**

**Passos:**
1. Abra o link no **Chrome, Edge ou Opera** (no computador — não funciona no celular nem no Firefox/Safari)
2. Conecte seu ESP32 por USB
3. Feche qualquer programa que esteja usando a porta serial (VS Code, PuTTY, monitor serial)
4. Clique em **⚡ INSTALAR AGORA ⚡**
5. Selecione a porta do ESP32 quando for solicitado
6. Espere ~30 segundos enquanto ele é flasheado
7. Pronto! Reinicie o ESP32 e você verá o splash do axolote 🦎

> **Se o flasheio falhar:** mantenha pressionado o botão `BOOT` do ESP32 enquanto clica em "INSTALAR AGORA", e solte quando começar a transferir.

Esta opção já inclui o patch do Deauther aplicado, então **todas as ferramentas funcionam out-of-the-box**.

------------

### 🛠️ Opção 2 · Compilar a partir do código-fonte

Se você quer modificar o firmware, adicionar features ou estudar o código, este é o caminho.

#### Pré-requisitos

1. **VS Code** ([baixar](https://code.visualstudio.com/))
2. **PlatformIO IDE** (extensão do VS Code — instalar pelo marketplace)
3. **Python 3** (vem com o PlatformIO)
4. **Driver USB do ESP32** (CP210x ou CH340, conforme seu módulo)

#### Clonar o repositório

```bash
git clone https://github.com/pepeangell5/ESP32-TOOLS.git
cd ESP32-TOOLS
```

#### Compilar e carregar

Abra a pasta no VS Code. O PlatformIO detectará automaticamente o `platformio.ini`. Basta clicar em:

1. **Build** (✓ na barra inferior)
2. Conecte o ESP32 por USB
3. **Upload** (→ na barra inferior)

O firmware será compilado (~3-5 minutos na primeira vez por causa de BLE + Evil Portal + ArduinoJson) e carregado no ESP32.

> **Importante:** se você compilar a partir do código-fonte e for usar as ferramentas Deauther ou Evil Portal no modo CLONE+Deauth, primeiro precisa aplicar o patch do SDK descrito mais abaixo.

### Primeiro boot

Algumas ferramentas (Clock & Weather) exigem conexão WiFi. Na primeira vez que você entrar em uma delas:

1. Aparecerá automaticamente o **scanner de redes**
2. Selecione sua rede WiFi 2.4GHz (o ESP32 não suporta 5GHz)
3. Digite a senha com o **teclado virtual** (UP/DOWN para navegar, OK para selecionar)
4. Conecte e salve — na próxima vez ele conectará automaticamente

Para esquecer a rede salva: `SYSTEM → Settings → FORGET WIFI`.

---

## 🔓 Patch para o Deauther

**Só necessário se você for usar as ferramentas Deauther ou Evil Portal no modo CLONE+Deauth.** A partir do framework Arduino-ESP32 versão 2.0.7+, a Espressif bloqueia a transmissão de frames de deauth via `esp_wifi_80211_tx()`. Este patch reverte esse bloqueio.

### Windows (PowerShell)

```powershell
C:\Users\SEU_USUARIO\.platformio\packages\toolchain-xtensa-esp32\bin\xtensa-esp32-elf-objcopy.exe --weaken-symbol=ieee80211_raw_frame_sanity_check C:\Users\SEU_USUARIO\.platformio\packages\framework-arduinoespressif32\tools\sdk\esp32\lib\libnet80211.a C:\Users\SEU_USUARIO\.platformio\packages\framework-arduinoespressif32\tools\sdk\esp32\lib\libnet80211.a
```

Substitua `SEU_USUARIO` pelo seu nome de usuário do Windows.

### Linux / macOS

```bash
~/.platformio/packages/toolchain-xtensa-esp32/bin/xtensa-esp32-elf-objcopy --weaken-symbol=ieee80211_raw_frame_sanity_check ~/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/lib/libnet80211.a ~/.platformio/packages/framework-arduinoespressif32/tools/sdk/esp32/lib/libnet80211.a
```

### Como funciona

`objcopy --weaken-symbol` marca a função `ieee80211_raw_frame_sanity_check` como "fraca". Isso permite que o firmware forneça sua própria versão, que sempre retorna 0 (já incluída em `Deauther.cpp`), fazendo com que todos os frames passem para o rádio.

> **Se você reinstalar o PlatformIO ou atualizar o framework, é preciso reaplicar o patch.**

---

## 📁 Estrutura do projeto

```
ESP32-TOOLS/
├── include/                    # Headers
│   ├── Pins.h                  # Definição de pinos
│   ├── PepeDraw.h              # Motor de fontes custom (5x7 + 8x12)
│   ├── MenuSystem.h            # Carrossel principal
│   ├── Icons.h                 # Sprites pixel art
│   ├── NVSStore.h              # Persistência
│   ├── SplashScreen.h
│   ├── Screensaver.h           # 🆕
│   ├── SoundUtils.h
│   ├── Settings.h
│   ├── SettingsMenu.h
│   ├── SystemInfo.h
│   ├── WifiScanner.h
│   ├── BeaconSpam.h
│   ├── Deauther.h
│   ├── EvilPortal.h            # 🆕
│   ├── EvilPortalHTML.h        # 🆕
│   ├── EvilPortalLogs.h        # 🆕
│   ├── ProbeSniffer.h          # 🆕
│   ├── Karma.h                 # 🆕
│   ├── BLEScanner.h
│   ├── BLESpam.h
│   ├── BTDisruptor.h
│   ├── RadioScanner.h
│   ├── RadioJammer.h
│   ├── PacketMonitor.h
│   ├── VirtualKeyboard.h       # 🆕 (módulo reutilizável)
│   ├── WifiConfig.h            # 🆕 (módulo reutilizável)
│   └── ClockWeather.h          # 🆕
├── src/                        # Implementações
│   ├── Main.cpp
│   └── [todos os .cpp]
├── img/                        # Capturas do projeto
├── platformio.ini              # Config do PlatformIO
├── LICENSE
└── README.md
```

---

## 🎮 Controles básicos

| Botão | Ação |
|:---|:---|
| **UP / DOWN** | Navegar menus, trocar modos |
| **OK (clique curto)** | Selecionar / entrar |
| **OK (segurar ~300-500ms)** | Sair / voltar |

O firmware usa detecção de pressionar curto vs. segurar para distinguir seleção de saída, evitando a necessidade de um 4º botão.

### No teclado virtual

| Botão | Ação |
|:---|:---|
| **UP / DOWN** | Navegar coluna por coluna (vertical primeiro) |
| **OK** | Selecionar a tecla atual |
| **SHIFT** | Toggle de maiúsculas + símbolos |
| **OK** sobre `OK` (verde) | Confirmar texto |
| **OK** sobre `X` (vermelho) | Cancelar |

---

## 🎨 Características de destaque

- **Fonte custom PepeDraw v2** — duas fontes próprias (5×7 small e 8×12 big) com ~220 glyphs, incluindo acentos do espanhol (á é í ó ú ñ ¿ ¡)
- **Splash screen animada** com o axolote pixel art (96x80): scan-in, type-on do texto e beeps ascendentes
- **Persistência em NVS** — configurações de som, contador de boots, credenciais WiFi e logs do Evil Portal sobrevivem a reinícios
- **Menus hierárquicos** com navegação consistente e animações slide
- **Paleta monocromática com acento laranja-vermelho** (UI_SELECT 0xFA20) — estilo Flipper/terminal retrô
- **Sons contextuais** por ferramenta — geiger no Spectrum, sirene no Packet Monitor em FLOODED, chirps de startup/exit
- **Screensaver do axolote** após 30 segundos sem atividade
- **Módulos reutilizáveis** — o teclado virtual e o WiFi config são funções helper que qualquer ferramenta pode invocar

---

## 🗺️ Roadmap futuro

Ideias para versões seguintes (pull requests são bem-vindos):

- [ ] **PMKID Attack** para captura de hashes WPA2
- [ ] **Indicador de bateria** em todos os headers (requer divisor de tensão com 2x 100kΩ no GPIO 36)
- [ ] **Case imprimível em 3D** com design dedicado
- [ ] **Suporte a cartão SD** (log de capturas, export pcap)
- [ ] **OTA updates** via web (aproveitando o WiFi Config existente)
- [ ] **Seletor manual de timezone** em Settings (para casos em que a geolocalização por IP falha)
- [ ] **Mais plataformas no Evil Portal** (Twitter/X, Netflix, bancos)

### ✅ Concluído na v2.0

- [x] Evil Portal (portal cativo com AP + DNS + captura de credenciais)
- [x] Probe Request Sniffer
- [x] KARMA Attack
- [x] Screensaver com animação do axolote
- [x] Relógio com NTP + clima ao vivo
- [x] WiFi Config persistente com teclado virtual

---

## 📜 Licença

Este projeto está sob a licença **MIT** — veja [LICENSE](LICENSE) para detalhes.

Em resumo: você pode usar, modificar e distribuir este código livremente, inclusive comercialmente, desde que inclua o copyright original.

---

## 🙌 Créditos e agradecimentos

- Inspiração geral: [Flipper Zero](https://flipperzero.one/), [ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder), [Bruce firmware](https://github.com/pr3y/Bruce), [Spacehuhn ESP8266 Deauther](https://github.com/SpacehuhnTech/esp8266_deauther)
- Bibliotecas: [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) (Bodmer), [RF24](https://github.com/nRF24/RF24) (TMRh20), [ArduinoJson](https://github.com/bblanchon/ArduinoJson) (Benoît Blanchon), Arduino-ESP32 (Espressif)
- APIs gratuitas: [ip-api.com](https://ip-api.com) (geolocalização por IP) e [Open-Meteo](https://open-meteo.com) (dados climáticos sem API key)
- Técnica do patch do SDK: comunidade Arduino-ESP32, [Jeija/esp32free80211](https://github.com/Jeija/esp32free80211)
- Protocolos BLE (Apple Continuity, Samsung, MS Swift Pair, Google Fast Pair): engenharia reversa pública da comunidade
- Mascote axolote: design original do projeto 🦎😎

---

## 📬 Contato

**José Ángel Chávez Félix (PepeAngell)**

- 📧 **Email:** [joseangelchavezfelix@gmail.com](mailto:joseangelchavezfelix@gmail.com)
- 📸 **Instagram:** [@esp32_tools](https://instagram.com/esp32_tools)
- 📘 **Facebook:** [ESP32-TOOLS](https://www.facebook.com/esp32tools/)
- 🐙 **GitHub:** [@pepeangell5](https://github.com/pepeangell5)

Se você gostou do projeto, ⭐ uma estrela no repo ajuda demais. Se você montar, me manda fotos — adoro ver o que outros makers fazem com ele.

---

<div align="center">

**Feito com ❤️ e 🌶️ em Los Mochis, Sinaloa, México**

*O conhecimento e a informação sempre devem ser gratuitos.*

</div>
