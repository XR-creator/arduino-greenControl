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
String input;
boolean isDebug = false;

void setup(){
  Serial.begin(9600);
  delay(300);
  initTime();
  relayInit();
  initSwimmers();
  initDriver();
}

void loop(){
  checkCommand();
  if (isDebug) {
    return;
  }
  
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
    startUp1();
  }
  if (currTemp0 <= MIN_TEMP_0) {
    startDown1();
  }
  if (currTemp0 >= MAX_TEMP_COOL) {
    relayCoolOn();
  }
  if (currTemp0 <= MIN_TEMP_COOL) {
    relayCoolOff();
  }
  // теплица 2 только фрамуга
  if (currTemp1 >= MAX_TEMP_1) {
    startUp2();
  }
  if (currTemp1 <= MIN_TEMP_1) {
    startDown2();
  }
  
  delay(1000);
}

//DEBUG

void checkCommand() {
  while(Serial.available()) {
    input = Serial.readString();
    
    Serial.print("<");
    Serial.println(input);

    Serial.print("> ");
    Serial.println(checkDebug(input));
  }
}

String checkDebug(String input) {
  input.trim();
  if (input.equals("debug on")) {
    isDebug = true;
    
    return "Переведено в режим отладки";
  }

  if (input.equals("debug off")) {
    isDebug = false;
    initTime();
    relayInit();
    initSwimmers();
    initDriver();
    
    return "Выведен из режима отладки";
  }

  if (isDebug) {
    // КУЛЕР
    if (input.equals("cooling on")) {
      relayCoolOn();
      
      return "Включен кулер";
    }
    if (input.equals("cooling off")) {
      relayCoolOff();
            
      return "Выключен кулер";
    }

    // ФРАМУГИ
    if (input.equals("startMotor up 1")) {
      startUp1();
            
      return "Включен мотор 1 на открытие";
    }
    
    if (input.equals("startMotor down 1")) {
      startDown1();
            
      return "Включен мотор 1 на закрытие";
    }
    if (input.equals("stopMotor 1")) {
      stopMotor1();
            
      return "Выключен мотор 1";
    }
    if (input.equals("startMotor up 2")) {
      startUp2();
            
      return "Включен мотор 2 на открытие";
    }
    if (input.equals("startMotor down 2")) {
      startDown2();
            
      return "Включен мотор 2 на закрытие";
    }
    if (input.equals("stopMotor 2")) {
      stopMotor2();
            
      return "Выключен мотор 2";
    }

    // НАСОСЫ
    if (input.equals("pump on")) {
      relayPumpOn();

      return "Помпа наполнение бака начато";
    }
    if (input.equals("pump off")) {
      relayPumpOff();

      return "Помпа наполнение бака выключена";
    }
    if (input.equals("rain on")) {
      relayRainOn();

      return "Полив выполняется";
    }
    if (input.equals("rain off")) {
      relayRainOff();

      return "Полив выключен";
    }

    // ТЕРМОМЕТРЫ
    if (input.equals("temp check 1")) {
      return "Температура теплицы 1: " + String(detectTemp(0));
    }
    if (input.equals("temp check 2")) {
      return "Температура теплицы 2: " + String(detectTemp(1));
    }
    if (input.equals("temp check")) {
      return "Температура теплицы 1: " + String(detectTemp(0)) + "\nТемпература теплицы 2: " + String(detectTemp(1));
    }

    // ПОПЛАВКИ
    if (input.equals("check hi level")) {
      return isHighLevel ? "Поднят" : "Опущен";
    }
    if (input.equals("check low level")) {
      return isLowLevel ? "Поднят" : "Опущен";
    }
    if (input.equals("check level")) {
      String firstVal = "Верхний поплавок: ";
      firstVal = firstVal + (isHighLevel ? "Поднят" : "Опущен");
      String secondVal = "\nНижний поплавок: ";
      secondVal = secondVal + (isLowLevel ? "Поднят" : "Опущен");
      
      return firstVal + secondVal;
    }

    // ЧАСЫ
    if (input.equals("time")) {
      printCurrTime();
      
      return "";
    }
  }

  if (input.equals("help")) {
    return "\ncooling on - Включить кулер\ncooling off - Выключить кулер\ndebug on - включение отладки\ndebug off - выключение отладки\nstartMotor [up/down] [1/2] - включение моторов фрамуги 1/2 в направлении up/down\nstopMotor [1/2] - выключение моторов фрамуг 1/2\npump [on/off] - включение(on)/выключение(off) помпы для наполнения бака\nrain [on/off] - включение(on)/выключение(off) помпы для полива\ntemp check [1/2/NONE] - отображение температуры с датчиков 1/2/все, если не укказано\ncheck [hi/low/NONE] level - отображение состояния поплавка(ов) верхнего(hi)/нижнего(low)/всех(ни чего не указано)\ntime - отображение текущего времени";
  }

  return "unknown command \"" + input + "\"";
}
