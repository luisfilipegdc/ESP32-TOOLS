# 🛒 Lista de compras — montar um "Bruce" do ZERO (base CYD)

> Situação real: você **não tem nada ainda** e vai começar comprando.
> Placa escolhida: **CYD (Cheap Yellow Display)** — um ESP32 com tela colorida
> 2.8" touch e slot de cartão SD embutido, suportado pelo firmware **Bruce**.
> Barato, com tela (não depende do celular) e dá pra crescer.
>
> Preços aproximados de **AliExpress (2026)**. No Mercado Livre / lojas BR costuma
> custar 2–3× mais, mas chega rápido. Todos os módulos externos são **3,3 V**.

---

## 🟡 A placa: CYD (ESP32-2432S028R)

- ESP32 (WiFi + Bluetooth) + **tela 2.8" colorida com toque** + **slot microSD**.
- Busque por: **`CYD ESP32-2432S028R`** ou **`Cheap Yellow Display 2.8`**.
- Usa cabo **micro-USB** (não USB-C). Grava o Bruce por um **PC** (Chrome desktop → bruce.computer/flasher).
- ⚠️ Ela **não faz BadUSB** (é ESP32 comum, não S3) — é o único recurso que fica de fora.

---

## 🥇 Tier 0 — Pra começar HOJE (o mínimo que já faz MUITA coisa)

Só com isto o Bruce já roda **todos os ataques de WiFi e Bluetooth** (que usam o
rádio interno do ESP32 — **não precisa de módulo nenhum**):

| Item | Habilita | Preço (US$) |
|---|---|---|
| **CYD (ESP32-2432S028R)** | a base: tela, WiFi, Bluetooth, SD | 9 – 12 |
| **MicroSD 16–32 GB** (FAT32) | salvar Evil Portal, capturas, scripts | 3 – 4 |
| Cabo micro-USB | gravar e alimentar (talvez você já tenha) | ~1 |

**Já faz:** Evil Portal (portal falso), Deauth, scan de redes, BLE scan, **BLE spam** (pop-ups em celulares), e mais.

**Subtotal Tier 0: ~US$ 13 – 17** (≈ R$ 75 – 95) ✅ *já é um aparelho útil*

---

## 🥈 Tier 1 — Primeiro upgrade (o poder mais "uau")

| Item | Habilita | Preço (US$) |
|---|---|---|
| **CC1101 + antena** | **SubGHz** (433 MHz): capturar/repetir controles de portão, campainhas, sensores | 3 – 5 |
| Jumpers Dupont (kit fêmea-fêmea) | ligar os módulos sem solda | ~2 |

**Subtotal Tier 1: ~US$ 5 – 7** (≈ R$ 30 – 40)

---

## 🥉 Tier 2 — Os outros poderes (conforme for aprendendo)

| Item | Habilita | Preço (US$) |
|---|---|---|
| **PN532 (NFC/RFID 13.56 MHz)** | ler / copiar / emular tags e cartões NFC | 6 – 9 |
| **Kit IR** (LED 940 nm + 2N2222 + receptor VS1838) | controle universal (TV, ar-condicionado) | 1 – 2 |
| **NRF24L01+** (3,3 V!) | 2.4 GHz: espectro / *jammer* | 1 – 2 |
| **GPS NEO-6M** | wardriving (mapear redes com localização) | 6 |
| **Bateria LiPo 3.7 V** (conector do CYD) | deixar portátil (senão use power bank) | 3 – 5 |
| Tags NFC/RFID virgens | praticar clonagem com segurança | ~3 |

**Subtotal Tier 2: ~US$ 20 – 27** (pegue só o que interessar)

---

## 💰 Resumo do orçamento

| Cenário | O que dá | Custo aprox. |
|---|---|---|
| **Começar hoje** (Tier 0) | WiFi + Bluetooth completos, com tela e SD | **~US$ 15** (≈ R$ 85) |
| **+ SubGHz** (Tier 0+1) | soma controles de portão/433 MHz | **~US$ 21** (≈ R$ 115) |
| **Bem equipado** (tudo) | quase todos os menus do Bruce | **~US$ 40** (≈ R$ 220) |

> Comparação: um **M5Stack Cardputer pronto ≈ US$ 80**. Começando pelo CYD,
> você tem um aparelho **funcionando com ~US$ 15** e cresce quando quiser. ✅

---

## 🔌 Notas importantes de montagem

- **Comece só com o CYD + SD.** WiFi e Bluetooth já rodam **sem nenhum módulo** — é a maior parte da diversão do Bruce. Os módulos vêm depois, um de cada vez.
- ⚠️ **O CYD tem POUCOS pinos livres** (tela + toque + SD já ocupam vários). Dá pra adicionar CC1101, NRF24, etc., mas é apertado — some **um módulo por vez** e confira o pinout da sua revisão da placa.
- **CC1101 e NRF24** usam o barramento **SPI** (podem compartilhar) + pinos de controle (CS/CE/GDO).
- **PN532** é mais fácil no modo **I²C** (2 fios: SDA/SCL).
- **Alimentação:** solde um **capacitor ~10 µF** no VCC do NRF24/CC1101 pra evitar reset.
- **Nunca** ligue módulos de 3,3 V no 5 V.

---

## ⚠️ Uso ético e legal (leia)

Isto é ferramenta de **estudo / Red Team**. Atacar WiFi, Bluetooth, copiar cartões
ou repetir sinais de rádio **só é legal em equipamentos e redes seus, ou com
autorização por escrito**. Contra terceiros é crime no Brasil (**Lei 12.737/2012**
e **Marco Civil**). **Jammers/bloqueadores são proibidos pela Anatel.** Use como
laboratório em casa. 🛡️

---

## 🛍️ Onde comprar

- **AliExpress** — mais barato (~2–4 semanas). Buscas: `CYD ESP32-2432S028R`,
  `CC1101 433MHz`, `PN532 NFC V3`, `NEO-6M GPS`, `nRF24L01`, `VS1838 IR`.
- **Mercado Livre / lojas BR** — 2–3× mais caro, mas chega em dias.
- Procure **kits de módulos Arduino** — às vezes sai mais em conta que peça avulsa.

---

*Documento de planejamento. Não é lista oficial do Bruce (AGPL, © BruceDevices).
Guia de compras pra montar um aparelho equivalente do zero, com foco em custo baixo.*
