#include <Adafruit_Sensor.h>
#include <DHT.h>

// --- Pinos ---
#define DHTPIN    15
#define DHTTYPE   DHT22
#define LDR_PIN   34
#define BTN_N     12
#define BTN_P     13
#define BTN_K     14
#define RELAY_PIN 2

// Relé do Wokwi costuma ser ativo-BAIXO:
#define RELAY_ON   LOW
#define RELAY_OFF  HIGH

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  pinMode(BTN_N, INPUT_PULLUP);
  pinMode(BTN_P, INPUT_PULLUP);
  pinMode(BTN_K, INPUT_PULLUP);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF); // começa desligado

  dht.begin();
}

void loop() {
  // Botões com PULLUP: pressionado = LOW → invertemos
  const int n = !digitalRead(BTN_N);
  const int p = !digitalRead(BTN_P);
  const int k = !digitalRead(BTN_K);

  // LDR -> pH (0..4095 → 0..14) com ponto flutuante
  const int   ldrValue = analogRead(LDR_PIN);
  const float ph       = (ldrValue / 4095.0f) * 14.0f;

  // DHT22 (pode retornar NaN em leituras iniciais)
  const float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("⚠️  DHT ainda sem leitura válida (NaN). Mantendo relé OFF.");
    digitalWrite(RELAY_PIN, RELAY_OFF);
    delay(1500);
    return;
  }

  const bool npk_ok = (n && p && k);
  const bool ph_ok  = (ph >= 6.0f && ph <= 7.0f);
  const bool seco   = (humidity < 40.0f);

  Serial.print("NPK: "); Serial.print(n); Serial.print(p); Serial.print(k);
  Serial.print(" | LDR raw: "); Serial.print(ldrValue);
  Serial.print(" | pH: "); Serial.print(ph, 2);
  Serial.print(" | Umidade: "); Serial.print(humidity, 2);
  Serial.print(" | Condições: ");
  Serial.print(npk_ok ? "NPK_OK " : "NPK_FAIL ");
  Serial.print(ph_ok  ? "pH_OK "  : "pH_FAIL ");
  Serial.println(seco ? "SECO"    : "UMIDO");

  if (npk_ok && ph_ok && seco) {
    digitalWrite(RELAY_PIN, RELAY_ON);
    Serial.println("💧 Irrigando (relé ON)...");
  } else {
    digitalWrite(RELAY_PIN, RELAY_OFF);
    Serial.println("⛔ Irrigação desligada (relé OFF).");
  }

  Serial.println("-----------------------------");
  delay(2000);
}