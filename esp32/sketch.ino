#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <DHT.h>

// WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "db4d4cf9edc946d1a5188a316414e105.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "estufa";
const char* mqtt_pass = "Estufa123";

// Sensores
#define DHTPIN 4
#define DHTTYPE DHT22
#define LDR_PIN 34

DHT dht(DHTPIN, DHTTYPE);

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println("Conectando WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (client.connect("ESP32Estufa", mqtt_user, mqtt_pass)) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falhou. rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  espClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  int ldrRaw = analogRead(LDR_PIN);
  float luminosidade = map(ldrRaw, 0, 4095, 0, 100);

  if (!isnan(temperatura) && !isnan(umidade)) {
    char tempStr[8], umidStr[8], lumStr[8];
    dtostrf(temperatura, 4, 2, tempStr);
    dtostrf(umidade, 4, 2, umidStr);
    dtostrf(luminosidade, 4, 2, lumStr);

    client.publish("estufa/temperatura", tempStr);
    client.publish("estufa/umidade", umidStr);
    client.publish("estufa/luminosidade", lumStr);

    Serial.printf("Temp: %s | Umidade: %s | Luz: %s\n", tempStr, umidStr, lumStr);
  }

  delay(5000);
}