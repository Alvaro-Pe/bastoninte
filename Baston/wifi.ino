#include <WiFi.h>

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";


void initWiFi() {
  Serial.println("Conectando al WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}


bool isWiFiConnected() {
  return WiFi.status() == WL_CONNECTED;
}


void reconnectWiFi() {
  if (!isWiFiConnected()) {
    Serial.println("WiFi desconectado. Reintentando...");
    
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long startAttemptTime = millis();

    while (!isWiFiConnected() && millis() - startAttemptTime < 5000) {
      delay(500);
      Serial.print(".");
    }

    if (isWiFiConnected()) {
      Serial.println("\nWiFi reconectado correctamente.");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("\nNo se pudo reconectar al WiFi.");
    }
  }
}