#define PIN_IN1 8
#define PIN_IN2 9

long timeWork = -1;

void initDriver() {
  pinMode (PIN_IN2, OUTPUT);
  pinMode (PIN_IN1, OUTPUT);

  startDown();
}

void startUp() {
  if (timeWork != -1 && isUp()) {
    return;
  }
  
  stopMotor();
  Serial.println("Пуск фрамуг открывание...");
  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN1, LOW);

  timeWork = millis();
}

boolean isUp() {
  return digitalRead(PIN_IN2) == HIGH && digitalRead(PIN_IN1) == LOW;
}

void startDown() {
  if (timeWork != -1 && isDown()) {
    return;
  }
  
  stopMotor();
  Serial.println("Пуск фрамуг закрывание...");
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN1, HIGH);
  timeWork = millis();
}

boolean isDown() {
  return digitalRead(PIN_IN2) == LOW && digitalRead(PIN_IN1) == HIGH;
}

void stopMotor() {
  Serial.println("Стоп фрамуг");
  digitalWrite(PIN_IN1, digitalRead(PIN_IN2));
  timeWork = -1;
}

boolean isStopMotor() {
  return digitalRead(PIN_IN2) == digitalRead(PIN_IN1);
}

void checkTimeWork(long lengthWork) {
  if (timeWork == -1) {
    return;
  }
  
  long currTime = millis();

  if ((currTime - timeWork) >= lengthWork) {
    stopMotor();
  }
}
