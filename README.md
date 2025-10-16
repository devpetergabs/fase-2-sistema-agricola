# FIAP - Faculdade de Informática e Administração Paulista

<p align="center">
<a href= "https://www.fiap.com.br/"><img src="assets/logo-fiap.png" alt="FIAP - Faculdade de Informática e Admnistração Paulista" border="0" width=40% height=40%></a>
</p>

<br>

## 💡 Nome do Projeto
**Sistema Agrícola Inteligente – Fase 2**

## 👨‍💻 Aluno
Gabriel Peter Ferreira  

## Link do ytb --> https://youtu.be/5-09AhAbPCc****

## 📘 Visão Geral
Este projeto tem como objetivo simular um **sistema automatizado de irrigação agrícola**, baseado em sensores de **umidade (DHT22)**, **luminosidade/pH (LDR/Potenciômetro)** e **níveis de nutrientes (botões NPK)**, utilizando uma **placa ESP32**.

O sistema foi desenvolvido em **C++ para Arduino**, e a simulação completa foi realizada no **[Wokwi](https://wokwi.com/)** — um ambiente virtual que permite testar o circuito e o código sem a necessidade de hardware físico.

---

## ⚙️ Componentes Utilizados
| Componente | Função | Pino ESP32 |
|-------------|--------|-------------|
| DHT22 | Sensor de umidade e temperatura | GPIO 15 |
| Potenciômetro (simula pH) | Conversor analógico para pH (0–14) | GPIO 34 |
| Botão N | Nutriente Nitrogênio | GPIO 12 |
| Botão P | Nutriente Fósforo | GPIO 13 |
| Botão K | Nutriente Potássio | GPIO 14 |
| Módulo Relé | Acionamento da bomba de irrigação | GPIO 2 |
| Fonte 3V3 / GND | Alimentação geral dos sensores | — |

---

## 🧩 Lógica do Sistema

### 🔹 Entrada de Dados
- **DHT22**: lê a **umidade do ar**, utilizada como referência para o nível de umidade do solo.
- **Potenciômetro**: converte o valor analógico (0–4095) em uma escala **de pH (0 a 14)**.
- **Botões (N, P, K)**: simulam sensores digitais de nutrientes essenciais do solo.  
  - Cada botão representa um nutriente ativo (pressionado = `1`).

---

### 🔹 Processamento
O código realiza as seguintes verificações a cada ciclo (loop):

```cpp
bool npk_ok = (n && p && k);
bool ph_ok  = (ph >= 6.0f && ph <= 7.0f);
bool seco   = (humidity < 40.0f);
