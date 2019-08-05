#define HOUR_START 13
#define HOUR_FILL 18
#define RAIN_MIN_LENGTH 30

#define MAX_TEMP_0 35
#define MIN_TEMP_0 28
#define MAX_TEMP_1 35
#define MIN_TEMP_1 28

#define MAX_TEMP_COOL 38
#define MIN_TEMP_COOL 33

#define LENGTH_MOTOR_WORK 96000

long startRain = -1;

void setup(){
  Serial.begin(9600);
  delay(300);
  initTime();
  relayInit();
  initSwimmers();
  initDriver();
}

void loop(){
  printCurrTime();
  
  boolean lowLevel = isLowLevel();
  boolean highLevel = isHighLevel();
  float currTemp0 = detectTemp(0);
  float currTemp1 = detectTemp(1);
  checkTimeWork(LENGTH_MOTOR_WORK);
  
  Serial.print("Текущая температура 1 теплицы: "); Serial.println(currTemp0);
  Serial.print("Текущая температура 2 теплицы: "); Serial.println(currTemp1);
  Serial.print("Уровень воды:"); Serial.print(lowLevel ? " малый" : ""); Serial.print(highLevel ? " большой" : "");Serial.println();

  // Налив бака
  if (!highLevel
        && checkTimeFill(HOUR_FILL)) {
    relayPumpOn();
  } else {
    relayPumpOff();
  }
 
  // Полив
  if (checkRainNow(HOUR_START) && !lowLevel) {
    relayRainOn();
    startRain = millis();
  }

  Serial.print("Полив: "); Serial.println(checkRainNow(HOUR_START));

  if (startRain != -1) {
    long lenExecutedMillis = millis() - startRain;
    
    if (RAIN_MIN_LENGTH <= (lenExecutedMillis / 1000 / 60)
          || lowLevel) {
      relayRainOff();
      startRain = -1;
    }
  } else {
    relayRainOff();
  }
  
  // Фрамуги
  // теплица 1 с вентилятором
  if (currTemp0 >= MAX_TEMP_0) {
    startUp();
  }
  if (currTemp0 <= MIN_TEMP_0) {
    startDown();
  }
  if (currTemp0 >= MAX_TEMP_COOL) {
    relayCoolOn();
  }
  if (currTemp0 <= MIN_TEMP_COOL) {
    relayCoolOff();
  }
  
  delay(1000);
}
