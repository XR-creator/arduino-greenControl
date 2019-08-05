#define PIN_HIGH_LEVEL 2
#define PIN_LOW_LEVEL 3

void initSwimmers() {
  digitalWrite(PIN_HIGH_LEVEL, 1);
  digitalWrite(PIN_LOW_LEVEL, 1);
}

// true - на стороне крепежа
boolean isLowLevel() {
  return digitalRead(PIN_LOW_LEVEL);
}

// true - на другое стороне от крепежа 
boolean isHighLevel() {
  return !digitalRead(PIN_HIGH_LEVEL);
}
