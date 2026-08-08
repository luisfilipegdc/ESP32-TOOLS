# 🛒 Lista de compras — componentes que faltam

> Você **já tem o ESP32-WROOM-32**. Esta lista é o que falta para (1) transformar
> a placa num **aparelho ESP32-TOOLS de verdade** (com tela) e (2) adicionar os
> recursos novos inspirados no Bruce (SubGHz, RFID, IR, GPS).
>
> **Sobre os links:** são links de **BUSCA** (não anúncio fixo) — assim sempre
> funcionam e você escolhe um vendedor bem avaliado. Preços aproximados de
> **AliExpress** (mais barato, ~2–4 semanas). No **Mercado Livre** custa 2–3× mais,
> mas chega em dias. **Confira as avaliações e a descrição antes de comprar.**

---

## 🥇 Tier 0 — Fazer o ESP32-TOOLS virar um aparelho (com tela)

*Prioridade máxima: sem isto o firmware não tem interface.*

| Componente | ~US$ | Comprar (busca) | O que conferir ✅ |
|---|---|---|---|
| **Tela TFT ILI9341 2.8" SPI** (com slot microSD) | 5–8 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=ILI9341%202.8%20SPI%20TFT) · [Mercado Livre](https://lista.mercadolivre.com.br/display-tft-ili9341-2.8-spi) | Que seja **SPI** (não paralela) e **ILI9341**. Ter slot de SD é ótimo. *(Eu adapto o firmware pra SPI.)* |
| **Botões táteis** (kit push-button 6×6) | 1–2 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=tactile%20push%20button%206x6) · [Mercado Livre](https://lista.mercadolivre.com.br/chave-tactil-push-button-6x6) | Precisa de **3** (mais uns extras). Os de 4 pernas 6×6mm são o padrão. |
| **Buzzer passivo** | 1 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=passive%20buzzer%20module%20arduino) · [Mercado Livre](https://lista.mercadolivre.com.br/buzzer-passivo-modulo) | **Passivo** (toca tons), não ativo. |
| **Protoboard 830 + kit de jumpers Dupont** | 3–4 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=breadboard%20830%20dupont%20jumper%20kit) · [Mercado Livre](https://lista.mercadolivre.com.br/protoboard-830-jumpers-dupont) | Pegue jumpers **macho-macho, macho-fêmea e fêmea-fêmea**. |
| **Cartão microSD 16–32 GB** | 3–4 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=micro%20sd%2016gb%20class%2010) · [Mercado Livre](https://lista.mercadolivre.com.br/cartao-micro-sd-16gb) | Classe 10. **Formatar em FAT32** (não exFAT). |

**Subtotal Tier 0: ~US$ 13–19** (≈ R$ 75–105)

---

## 🥈 Tier 1 — Rádio 2.4 GHz (espectro/jammer — já é feature)

| Componente | ~US$ | Comprar (busca) | O que conferir ✅ |
|---|---|---|---|
| **NRF24L01 PA+LNA** (com antena) | 3–4 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=nRF24L01%20PA%20LNA%20antenna) · [Mercado Livre](https://lista.mercadolivre.com.br/nrf24l01-pa-lna-antena) | Versão **PA+LNA** com **antena SMA 2.4GHz inclusa** (mais alcance). |
| **Adaptador NRF24** (regulador 3.3V + capacitor) *opcional mas recomendado* | 1 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=nRF24L01%20adapter%20breakout%20AMS1117) · [Mercado Livre](https://lista.mercadolivre.com.br/adaptador-nrf24l01-socket) | Estabiliza a alimentação (o NRF24 é sensível). Evita resets. |

> 💡 Quer a ideia do **"RF-KILL" (dual NRF24)**? Compre **2 unidades** do PA+LNA — depois a gente turbina o espectro/jammer pra usar os dois.

**Subtotal Tier 1: ~US$ 4–5** (≈ R$ 22–28) por rádio

---

## 🥉 Tier 2 — Recursos novos (inspirados no Bruce)

| Componente | ~US$ | Comprar (busca) | O que conferir ✅ |
|---|---|---|---|
| **CC1101 433 MHz** (com antena) — SubGHz | 3–5 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=CC1101%20433MHz%20module%20antenna) · [Mercado Livre](https://lista.mercadolivre.com.br/modulo-cc1101-433mhz-antena) | **433 MHz** (portões BR) com **antena de 433MHz** (a molinha). ⚠️ Não é a antena de 2.4GHz! |
| **PN532** (NFC/RFID 13.56 MHz) | 6–9 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=PN532%20NFC%20module%20V3) · [Mercado Livre](https://lista.mercadolivre.com.br/pn532-nfc-modulo) | Versão **V3**. Costuma vir com 1 cartão + 1 tag de brinde. Usar em modo **I²C**. |
| **Kit IR** (LED 940nm + receptor VS1838 + transistor) | 1–2 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=infrared%20940nm%20LED%20VS1838%20receiver%20kit) · [Mercado Livre](https://lista.mercadolivre.com.br/kit-emissor-receptor-infravermelho-vs1838) | LED emissor **940nm** + receptor **VS1838/TSOP**. |
| **GPS NEO-6M** (com antena) — wardriving | 6 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=GPS%20NEO-6M%20module%20antenna) · [Mercado Livre](https://lista.mercadolivre.com.br/gps-neo-6m-modulo-antena) | Vem com **antena cerâmica** (plug U.FL) inclusa. |

**Subtotal Tier 2: ~US$ 16–22** (≈ R$ 90–120) — pegue só o que interessar.

---

## 🔋 Bateria (deixar portátil) — opcional

| Componente | ~US$ | Comprar (busca) | O que conferir ✅ |
|---|---|---|---|
| **18650 + suporte + módulo TP4056** | 5–7 | [AliExpress](https://www.aliexpress.com/wholesale?SearchText=18650%20holder%20TP4056%20charging) · [Mercado Livre](https://lista.mercadolivre.com.br/suporte-18650-tp4056-carregador) | TP4056 **com proteção** (DW01). Célula 18650 de marca (cuidado com falsas). |

---

## 💰 Resumo

| Etapa | O que dá | Custo aprox. |
|---|---|---|
| **Só Tier 0** | ESP32-TOOLS funcionando com tela, botões e SD | **~US$ 16** (≈ R$ 90) |
| **Tier 0 + 1** | + espectro/jammer 2.4 GHz com alcance | **~US$ 20** (≈ R$ 115) |
| **Tudo (0+1+2)** | + SubGHz, RFID/NFC, IR e GPS | **~US$ 40** (≈ R$ 225) |

> **Sugestão de ordem de compra:** comece pelo **Tier 0** (faz o aparelho existir),
> some o **NRF24 PA+LNA** (feature que já está no código), e depois vá pegando os
> módulos do Tier 2 conforme for aprendendo — um de cada vez.

---

## ⚠️ Dicas rápidas pra não errar

- **Antena tem que casar com a frequência:** 2.4GHz (NRF24) ≠ 433MHz (CC1101). Compre cada módulo **com a antena certa inclusa**.
- **Cuidado SMA × RP-SMA:** conectores parecidos, incompatíveis. Comprar módulo **com antena junto** evita o problema.
- **Tudo 3,3 V:** nunca ligue os módulos no 5 V dos pinos.
- **Tela: compre SPI** (não paralela). Eu ajusto o firmware pra ela.

---

*Documento de planejamento de compras. Links de busca (não anúncios fixos). Preços e
disponibilidade variam. Projeto ESP32-TOOLS sob licença MIT 🦎.*
