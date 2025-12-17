#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String s = Serial.readStringUntil('\n');
    s.trim();
    Serial.print("Sent: ");
    Serial.println(s);
    Serial1.println(s); 
  }
  if (Serial1.available() > 0) {
    String s1 = Serial1.readStringUntil('\n');
    s1.trim();
    Serial.print("Received: ");
    Serial.println(s1);
  }
}