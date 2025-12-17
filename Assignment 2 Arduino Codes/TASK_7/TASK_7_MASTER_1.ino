#include <Wire.h>

void setup(){
  Wire.begin();       
} 

void loop(){
  int a,b;
  Wire.requestFrom(6, 2);   
  if (Wire.available()){
    a = Wire.read();
  }
  Wire.requestFrom(7, 2);   
  if (Wire.available()){
    b = Wire.read();
  }
  Wire.beginTransmission(0);
  Wire.write(a+b);
  Wire.endTransmission();
  delay(500);
}