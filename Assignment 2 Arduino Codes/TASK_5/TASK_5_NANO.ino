#include <Wire.h>

void setup(){
  Wire.begin();
  Wire.onReceive(receiveEvent);
  Serial.begin();
}

void loop(){
  delay(100);
}

void receiveEvent(int howMany){
  char c = Wire.read();
  Serial.print(c);
  Serial.println();
}