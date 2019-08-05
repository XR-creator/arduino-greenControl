#define PIN_RELAY_PUMP 4
#define PIN_RELAY_RAIN 5
#define PIN_RELAY_COOL 6

void relayInit() { 
  pinMode(PIN_RELAY_PUMP, OUTPUT);
  digitalWrite(PIN_RELAY_PUMP, HIGH);

  pinMode(PIN_RELAY_RAIN, OUTPUT);
  digitalWrite(PIN_RELAY_RAIN, HIGH);

  pinMode(PIN_RELAY_COOL, OUTPUT);
  digitalWrite(PIN_RELAY_COOL, HIGH);
}

void relayRainOn() {
  digitalWrite(PIN_RELAY_RAIN, LOW);
  Serial.println("Полив: идет");
}

void relayRainOff() {
  digitalWrite(PIN_RELAY_RAIN, HIGH);
  Serial.println("Полив: не идет");
}

void relayCoolOn() {
  digitalWrite(PIN_RELAY_COOL, LOW);
  Serial.println("Обдув: происходит");
}

void relayCoolOff() {
  digitalWrite(PIN_RELAY_COOL, HIGH);
  Serial.println("Обдув: не происходит");
}

void relayPumpOn() {
  digitalWrite(PIN_RELAY_PUMP, LOW);
  Serial.println("Бак: наполняется");
}

void relayPumpOff() {
  digitalWrite(PIN_RELAY_PUMP, HIGH);
  Serial.println("Бак: наполнен");
}
