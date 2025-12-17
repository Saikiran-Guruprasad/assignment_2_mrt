#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3);

void setup() {
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available() > 0) {
    String s = Serial1.readStringUntil('\n');
    s.trim();
    Serial1.println(s);
  }
}