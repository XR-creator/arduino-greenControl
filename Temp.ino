#include <OneWire.h>

OneWire ds0(12);
OneWire ds1(13);

float detectTemp(int number){
  byte data[2];

  OneWire ds = ds0;
  if (number == 1) {
    ds = ds1;
  }
  
  ds.reset();
  ds.write(0xCC);
  ds.write(0x44);
  
  delay(1000);
  
  ds.reset();
  ds.write(0xCC); 
  ds.write(0xBE);
  
  data[0] = ds.read();
  data[1] = ds.read();

  float temperature =  ((data[1] << 8) | data[0]) * 0.0625;

  //Serial.print("Temp[");Serial.print(number);Serial.print("]=");Serial.println(temperature);

  return temperature;
}
