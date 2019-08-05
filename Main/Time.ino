#include <Time.h>  
#include <Wire.h>  
#include <DS1307RTC.h>

int lastExecutedDay = -1;

void initTime() {
  setSyncProvider(RTC.get);
  if(timeStatus()!= timeSet) {
     Serial.println("Не удалось синхронизироваться с часами");
  }
}

boolean checkRainNow(int hourStart) {
  Serial.print("Hour: ");Serial.println(hour());
  boolean inTime = (hourStart == hour());

  if (!inTime) {
    return false;
  }

  if (day() == lastExecutedDay) {
    return false; 
  }

  lastExecutedDay = day();
  
  return true;  
}

boolean checkTimeFill(int hourStart) {
  return hour() == hourStart;
}

void printCurrTime(){
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
