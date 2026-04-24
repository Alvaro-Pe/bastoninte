#define BUZZER_PIN 19
#define VIBRATION_PIN 21

// 🔧 Configuración inicial
void initActuators() {
  pinMode(VIBRATION_PIN, OUTPUT);

  ledcAttach(BUZZER_PIN, 1000, 8);

  digitalWrite(VIBRATION_PIN, LOW);
  ledcWriteTone(BUZZER_PIN, 0);
}

// 🔊 Encender buzzer
void turnBuzzerOn() {
  ledcWriteTone(BUZZER_PIN, 1000);
}

// 🔇 Apagar buzzer
void turnBuzzerOff() {
  ledcWriteTone(BUZZER_PIN, 0);
}

// 📳 Encender vibración (LED en tu caso)
void turnVibrationOn() {
  digitalWrite(VIBRATION_PIN, HIGH);
}

// 📳 Apagar vibración
void turnVibrationOff() {
  digitalWrite(VIBRATION_PIN, LOW);
}