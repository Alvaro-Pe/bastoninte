#define TRIG_PIN 5
#define ECHO_PIN 18

struct SensorData {
  float distance;
  float latitude;
  float longitude;
};

//  Distancia REAL
float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  return distance;
}

//  GPS SIMULADO
float readLatitude() {
  return 4.6097;
}

float readLongitude() {
  return -74.0817;
}

//  Lectura general
SensorData readAllSensors() {
  SensorData data;

  data.distance = readDistance();
  data.latitude = readLatitude();
  data.longitude = readLongitude();

  return data;
}