#define PIN_IN1 8
#define PIN_IN2 9

#define PIN_IN3 10
#define PIN_IN4 11

long timeWork1 = -1;
long timeWork2 = -1;

void initDriver() {
  pinMode (PIN_IN2, OUTPUT);
  pinMode (PIN_IN1, OUTPUT);
  
  pinMode (PIN_IN3, OUTPUT);
  pinMode (PIN_IN4, OUTPUT);

  startDown1();
  startDown2();
}

void startUp1() {
  if (timeWork1 != -1 && isUp1()) {
    return;
  }
  
  stopMotor1();
  Serial.println("Пуск фрамуги 1 открывание...");
  digitalWrite(PIN_IN2, HIGH);
  digitalWrite(PIN_IN1, LOW);

  timeWork1 = millis();
}

boolean isUp1() {
  return digitalRead(PIN_IN2) == HIGH && digitalRead(PIN_IN1) == LOW;
}

void startUp2() {
  if (timeWork2 != -1 && isUp2()) {
    return;
  }
  
  stopMotor2();
  Serial.println("Пуск фрамуги 2 открывание...");
  digitalWrite(PIN_IN4, HIGH);
  digitalWrite(PIN_IN3, LOW);

  timeWork2 = millis();
}

boolean isUp2() {
  return digitalRead(PIN_IN4) == HIGH && digitalRead(PIN_IN3) == LOW;
}

void startDown1() {
  if (timeWork1 != -1 && isDown1()) {
    return;
  }
  
  stopMotor1();
  Serial.println("Пуск фрамуги 1 закрывание...");
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN1, HIGH);
  timeWork1 = millis();
}

boolean isDown1() {
  return digitalRead(PIN_IN2) == LOW && digitalRead(PIN_IN1) == HIGH;
}

void stopMotor1() {
  Serial.println("Стоп фрамуги 1");
  digitalWrite(PIN_IN1, digitalRead(PIN_IN2));
  timeWork1 = -1;
}

boolean isStopMotor1() {
  return digitalRead(PIN_IN2) == digitalRead(PIN_IN1);
}

void startDown2() {
  if (timeWork2 != -1 && isDown2()) {
    return;
  }
  
  stopMotor2();
  Serial.println("Пуск фрамуги 2 закрывание...");
  digitalWrite(PIN_IN4, LOW);
  digitalWrite(PIN_IN3, HIGH);
  timeWork2 = millis();
}

boolean isDown2() {
  return digitalRead(PIN_IN4) == LOW && digitalRead(PIN_IN3) == HIGH;
}

void stopMotor2() {
  Serial.println("Стоп фрамуги 2");
  digitalWrite(PIN_IN3, digitalRead(PIN_IN4));
  timeWork2 = -1;
}

void checkTimeWork(long lengthWork) {
  if (timeWork1 != -1) {
    long currTime = millis();

    if ((currTime - timeWork1) >= lengthWork) {
      stopMotor1();
    }
  }
  
  if (timeWork2 != -1) {
    long currTime = millis();

    if ((currTime - timeWork2) >= lengthWork) {
      stopMotor2();
    }
  }
}
