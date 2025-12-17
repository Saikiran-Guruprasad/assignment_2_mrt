#include <Wire.h>

const int a = 2;

void setup() {
  Wire.begin(4);               
  Wire.onRequest(requestEvent); 
}

void loop() {
  delay(100);
}

void requestEvent() {
  Wire.write(a); 
}