# 🛒 Lista de peças — montar um multi-tool completo (estilo Bruce)

> Objetivo: transformar o hardware que você **já tem** (do ESP32-TOOLS) num
> aparelho completo estilo **Bruce**, comprando só os módulos que faltam —
> por **muito menos** que os ~US$ 80 de um Cardputer pronto.
>
> Todos os módulos abaixo são **3,3 V** (o mesmo do ESP32), então **não precisa
> de conversor de nível**. Preços aproximados de **AliExpress (2026)** — no
> Mercado Livre costuma custar 2–3× mais, mas chega rápido e é nacional.

---

## ✅ O que você JÁ tem (do ESP32-TOOLS) — custo R$ 0

| Peça | Serve pra |
|---|---|
| ESP32-WROOM-32 | cérebro (WiFi + Bluetooth) |
| Tela TFT ILI9341 | interface / menus |
| 3 botões | navegação |
| Buzzer | avisos sonoros |
| NRF24L01 | rádio 2.4 GHz (spectrum / jammer / BLE spam) |

Já cobre **WiFi, Bluetooth e 2.4 GHz**. Falta o resto dos "poderes" do Bruce. 👇

---

## 🥇 Tier 1 — Essencial (o que falta pra "virar Bruce")

| Peça | Pra que serve | Preço aprox. (US$) |
|---|---|---|
| **CC1101 + antena** | **SubGHz** (433/868/915 MHz): capturar/repetir controles de portão, sensores, etc. | 3 – 5 |
| **Bateria 18650 + suporte + módulo TP4056** | deixar **portátil** e recarregável por USB | 5 – 7 |
| **MicroSD 16 GB** (se a sua tela não tiver slot) | guardar portais, capturas, scripts | 3 |

**Subtotal Tier 1: ~US$ 11 – 15** (≈ R$ 60 – 85)

---

## 🥈 Tier 2 — Os "poderes" clássicos do Bruce

| Peça | Pra que serve | Preço aprox. (US$) |
|---|---|---|
| **PN532 (NFC/RFID 13.56 MHz)** | ler / escrever / **emular** cartões e tags NFC | 6 – 9 |
| **Kit IR** (LED 940 nm + transistor 2N2222 + receptor VS1838) | virar **controle universal** (TV, ar-condicionado…) | 1 – 2 |
| **RDM6300 (RFID 125 kHz)** *(opcional)* | ler tags/crachás de 125 kHz | 2 |

**Subtotal Tier 2: ~US$ 9 – 13** (≈ R$ 50 – 72)

---

## 🥉 Tier 3 — Avançado / opcional

| Peça | Pra que serve | Preço aprox. (US$) |
|---|---|---|
| **ESP32-S3 DevKit** | só se quiser **BadUSB** de verdade (o WROOM-32 não tem USB nativo) | 6 – 8 |
| **GPS NEO-6M** | **wardriving** (mapear redes com localização) | 6 |
| **RDA5807 (rádio FM)** | ouvir/mexer com FM | 2 |
| **NRF24 PA+LNA** | mesma função do seu NRF24, com **mais alcance** | 3 |

**Subtotal Tier 3: ~US$ 17** (≈ R$ 95) — pegue só o que te interessar.

---

## 💰 Resumo do orçamento

| Cenário | Custo aprox. |
|---|---|
| **Mínimo** (Tier 1) — já vira um Bruce com SubGHz + portátil | **~US$ 12** (≈ R$ 65) |
| **Recomendado** (Tier 1 + 2) — Bruce "de verdade", bem completo | **~US$ 22** (≈ R$ 120) |
| **Full** (Tier 1 + 2 + 3) — tudo, incluindo BadUSB e GPS | **~US$ 38** (≈ R$ 210) |

> Comparação: um **M5Stack Cardputer pronto ≈ US$ 80**. Montando você mesmo e
> reaproveitando o que já tem, o **completo sai por menos da metade**. ✅

---

## 🔌 Notas de ligação (importante)

- **CC1101, NRF24 e o cartão SD** dividem o **mesmo barramento SPI** (MOSI/MISO/SCK)
  — cada um só precisa do seu próprio pino **CS/SS** separado.
- O **PN532** é mais fácil no modo **I²C** (só 2 fios: SDA + SCL) — economiza pinos.
- O **IR** usa **2 pinos**: um pro LED (transmitir) e um pro receptor VS1838.
- **Alimentação:** o CC1101 e o NRF24 PA+LNA puxam picos de corrente — solde um
  **capacitor de ~10 µF** entre 3,3 V e GND perto de cada módulo pra evitar reset.
- Tudo **3,3 V**: **não** ligue nada em 5 V direto nos pinos do ESP32.

---

## 🛍️ Onde comprar

- **AliExpress** — mais barato, demora ~2–4 semanas. Busque: `CC1101 433MHz module`,
  `PN532 NFC module V3`, `TP4056 18650`, `NEO-6M GPS`, `VS1838 IR receiver`.
- **Mercado Livre / lojas BR** — 2–3× mais caro, porém chega em dias e sem imposto surpresa.
- Dica: procure **kits** de "módulos Arduino" — às vezes vem IR + sensores + jumpers junto e sai em conta.

---

*Documento de planejamento. Não é lista oficial do projeto Bruce (AGPL, © BruceDevices).
Serve como guia de compras pra quem quer montar um aparelho equivalente reaproveitando peças.*
