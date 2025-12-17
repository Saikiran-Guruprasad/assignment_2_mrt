#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(9600);
}

void loop(){
  Wire.beginTransmission();
  Wire.write("ALL IS WELL");
  Wire.endTransmission();
  delay(500);
}
