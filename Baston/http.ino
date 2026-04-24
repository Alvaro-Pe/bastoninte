#include <WiFi.h>
#include <HTTPClient.h>

// 🌐 URL de tu servidor (cámbiala cuando montes tu API)
const char* SERVER_URL = "http://tu-servidor.com/baston.php?data=1";


// 📦 FORMATEAR DATOS A JSON
String buildJson(SensorData data) {
  String json = "{";

  json += "\"distance\":" + String(data.distance, 2) + ",";
  json += "\"latitude\":" + String(data.latitude, 6) + ",";
  json += "\"longitude\":" + String(data.longitude, 6);

  json += "}";

  return json;
}

// ENVIAR DATOS POR HTTP
void sendDataHTTP(SensorData data) {

  // 🔌 verificar WiFi
  if (!isWiFiConnected()) {
    Serial.println("❌ No hay WiFi. No se puede enviar HTTP.");
    return;
  }

  HTTPClient http;

  // 🌐 iniciar conexión
  http.begin(SERVER_URL);
  http.addHeader("Content-Type", "application/json");

  // 📦 crear JSON
  String json = buildJson(data);

  // 🚀 enviar POST
  int httpResponseCode = http.POST(json);

  // 📊 respuesta del servidor
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  // 🔚 cerrar conexión
  http.end();
}