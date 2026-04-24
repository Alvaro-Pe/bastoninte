#include <HTTPClient.h>
#include <ArduinoJson.h>

// 🌐 Endpoint para leer estado del buzzer
const char* BUZZER_STATE_URL = "http://tu-servidor.com/baston.php?getBuzzer=1";

// 🌐 Endpoint para resetear buzzer
const char* RESET_BUZZER_URL = "http://tu-servidor.com/baston.php?resetBuzzer=1";


// 📡 Leer estado del buzzer desde la BD (via PHP)
int getBuzzerState() {

  HTTPClient http;

  http.begin(BUZZER_STATE_URL);

  int httpCode = http.GET();

  if (httpCode > 0) {

    String payload = http.getString();
    Serial.print("📥 Respuesta JSON: ");
    Serial.println(payload);

    // 📦 parsear JSON
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.print("❌ Error JSON: ");
      Serial.println(error.c_str());
      http.end();
      return 0;
    }

    int estado = doc["estado"];

    http.end();
    return estado;
  }

  http.end();
  return 0;
}


// 🔄 Resetear estado del buzzer en BD
void resetBuzzerState() {

  HTTPClient http;

  http.begin(RESET_BUZZER_URL);

  int httpCode = http.GET();

  Serial.print("🔄 Reset buzzer HTTP code: ");
  Serial.println(httpCode);

  http.end();
}


// 🔥 FUNCIÓN PRINCIPAL DE CONTROL
void handleCommands() {

  int estado = getBuzzerState();

  if (estado == 1) {

    Serial.println("🔊 Buzzer activado desde la web");

    turnBuzzerOn();
    turnVibrationOn();

    delay(10000);

    turnBuzzerOff();
    turnVibrationOff();

    Serial.println("🔇 Buzzer apagado automáticamente");

    resetBuzzerState();
  }
}