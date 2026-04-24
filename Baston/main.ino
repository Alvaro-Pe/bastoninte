struct SensorData {
  float distance;
  float latitude;
  float longitude;
};

unsigned long lastGpsSend = 0;
const int gpsInterval = 10000; // 10 segundos

unsigned long lastCommandCheck = 0;
const unsigned long commandInterval = 300000; // 5 minutos

// ⏱️ para HTTP
unsigned long lastHttpSend = 0;
const int httpInterval = 5000;

void setup() {
  Serial.begin(115200);

  // 🔧 Sensores
  pinMode(5, OUTPUT);   // TRIG
  pinMode(18, INPUT);   // ECHO

  // 📳 Actuadores
  initActuators();

  // 📡 WiFi
  initWiFi();

  while (!isWiFiConnected()) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
}

void loop() {

  reconnectWiFi();

  if (millis() - lastCommandCheck >= commandInterval) {
  lastCommandCheck = millis();

  Serial.println("🔍 Revisando comandos de la web...");
  handleCommands();
}

  //  leer sensores
  SensorData data = readAllSensors();

  //  distancia
  Serial.print("Distancia: ");
  Serial.print(data.distance);
  Serial.println(" cm");

  // lógica del bastón
  if (data.distance <= 100) {
    int delayTime = map(data.distance, 1, 100, 100, 800);

    turnBuzzerOn();
    turnVibrationOn();

    delay(300);

    turnBuzzerOff();
    turnVibrationOff();

    delay(delayTime);

  } else {
    turnBuzzerOff();
    turnVibrationOff();
  }

  //  GPS cada 10s
  if (millis() - lastGpsSend >= gpsInterval) {
    lastGpsSend = millis();

    Serial.println("📍 Ubicación:");
    Serial.print("Lat: ");
    Serial.println(data.latitude, 6);

    Serial.print("Lng: ");
    Serial.println(data.longitude, 6);
  }

  //  ENVÍO HTTP 
  if (millis() - lastHttpSend >= httpInterval) {
    lastHttpSend = millis();

    Serial.println("📡 Enviando datos al servidor...");
    sendDataHTTP(data);
  }

  delay(50);
}