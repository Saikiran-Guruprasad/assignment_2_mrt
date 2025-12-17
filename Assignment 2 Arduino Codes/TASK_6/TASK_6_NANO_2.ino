#include <Wire.h>

const int b = 3;

void setup() {
  Wire.begin(5);               
  Wire.onRequest(requestEvent); 
}

void loop() {
  delay(100);
}

void requestEvent() {
  Wire.write(b); 
}