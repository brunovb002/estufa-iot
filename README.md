# 🌱 Estufa Inteligente — Monitoramento IoT

Projeto de monitoramento inteligente de estufa utilizando ESP32, MQTT e Node-RED, desenvolvido para a disciplina de **Disruptive Architectures: IoT, IoB & Generative IA** da FIAP.

---

## 📋 Descrição do Projeto

Sistema de monitoramento em tempo real das condições internas de uma estufa (temperatura, umidade e luminosidade), com comparação de dados climáticos externos via API pública e persistência em banco de dados MySQL.

O sistema simula o monitoramento de uma estufa agrícola, permitindo que produtores acompanhem as condições internas e comparem com o clima externo para tomar decisões como acionar irrigação, ventilação ou iluminação artificial.

---

## 🏗️ Arquitetura da Solução

```
Wokwi (ESP32 + DHT22 + LDR)
        ↓ MQTT over TLS (porta 8883)
HiveMQ Cloud (Broker MQTT)
        ↓
Node-RED (local)
   ├── Dashboard em tempo real (Gauges, Gráficos, Tabela)
   ├── MySQL (persistência das leituras)
   └── OpenWeatherMap API (clima externo para comparação)
```

**Tópicos MQTT utilizados:**
- `estufa/temperatura`
- `estufa/umidade`
- `estufa/luminosidade`

---

## 🛠️ Tecnologias Utilizadas

| Tecnologia | Função |
|---|---|
| ESP32 | Microcontrolador principal |
| DHT22 | Sensor de temperatura e umidade |
| LDR | Sensor de luminosidade |
| MQTT (TLS) | Protocolo de comunicação IoT |
| HiveMQ Cloud | Broker MQTT gratuito na nuvem |
| Node-RED | Processamento, automação e dashboard |
| MySQL 8.0 | Banco de dados para persistência |
| OpenWeatherMap API | Dados climáticos externos em tempo real |
| Wokwi | Simulador de hardware ESP32 |

---

## 📦 Pré-requisitos

- [Node.js LTS](https://nodejs.org)
- [MySQL 8.0](https://dev.mysql.com/downloads/mysql/)
- Node-RED (`npm install -g node-red`)
- Conta gratuita no [HiveMQ Cloud](https://www.hivemq.com/mqtt-cloud-broker/)
- Conta gratuita no [OpenWeatherMap](https://openweathermap.org)

---

## 🚀 Instruções de Execução

### 1. Banco de dados

Execute o script de criação do banco:

```bash
mysql -u root -p < database/schema.sql
```

### 2. Node-RED

Instale os nodes necessários:

```bash
npm install -g node-red-node-mysql
npm install -g node-red-dashboard
npm install -g node-red-node-ui-table
```

Inicie o Node-RED:

```bash
node-red
```

Acesse [http://localhost:1880](http://localhost:1880), vá em **Menu > Import** e importe o arquivo `node-red/flows.json`.

### 3. Configurar credenciais no Node-RED

Após importar o fluxo, configure as credenciais nos seguintes nós:

**Broker MQTT (HiveMQ):**
- Clique dois vezes em qualquer nó MQTT (Temperatura, Umidade ou Luminosidade)
- Clique no lápis ao lado do campo Servidor
- Preencha com a URL do seu cluster, porta 8883 e marque TLS
- Na aba Segurança, insira seu usuário e senha do HiveMQ

**MySQL:**
- Clique dois vezes no nó MySQL Estufa
- Insira host `127.0.0.1`, porta `3306`, banco `estufa_iot`, usuário e senha

**OpenWeatherMap:**
- Clique dois vezes no nó HTTP Request (OpenWeatherMap)
- Na URL, substitua `SUA_API_KEY_OPENWEATHERMAP` pela sua chave da API

Clique em **Deploy** para salvar.

### 4. Simulação ESP32

Acesse o projeto no Wokwi:
👉 [https://wokwi.com/projects/463031862075942913](https://wokwi.com/projects/463031862075942913)

Clique em **Play** para iniciar. O ESP32 publicará temperatura, umidade e luminosidade via MQTT a cada 5 segundos.

### 5. Dashboard

Acesse o dashboard em tempo real:
👉 [http://localhost:1880/ui](http://localhost:1880/ui)

---

## 📊 Funcionalidades do Dashboard

- **Gauges internos** — temperatura, umidade e luminosidade da estufa
- **Gauges externos** — temperatura e umidade via OpenWeatherMap
- **Gráficos de linha** — histórico das variáveis ao longo do tempo
- **Tabela de leituras** — últimas 10 leituras salvas no MySQL

---

## 📁 Estrutura do Repositório

```
estufa-iot/
├── esp32/
│   └── sketch.ino          # Código do ESP32
├── node-red/
│   └── flows.json          # Fluxo exportado do Node-RED
├── database/
│   └── schema.sql          # Script de criação do banco MySQL
└── README.md
```

---

## 👥 Integrantes

| Nome | RM |
|---|---|
| Bruno Vinicius Barbosa | RM566366 |
| Guilherme de Andrade Martini | RM560870 |
| Raphael Gomes Mancera | RM562279 |
---

## 🏫 FIAP — 2026