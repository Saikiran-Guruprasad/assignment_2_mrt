#include <Wire.h>

void setup(){
  Wire.begin();       
} 

void loop(){
  int c,d;
  Wire.requestFrom(6, 2);   
  if (Wire.available()){
     c = Wire.read();
  }
  Wire.requestFrom(7, 2);   
  if (Wire.available()){
    d = Wire.read();
  }
  Wire.beginTransmission(0);
  Wire.write(c+d);
  Wire.endTransmission();
  delay(500);
}