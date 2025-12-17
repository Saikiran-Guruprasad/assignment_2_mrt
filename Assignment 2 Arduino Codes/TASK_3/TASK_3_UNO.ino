#include<SPI.h>

const int SS_PIN = 10;

void setup(){
  Serial.begin(9600);
  pinMode(SS_PIN,OUTPUT);
  digitalWrite(SS_PIN,HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop(){
  if (Serial.available()>0){
    String s = Serial.readStringUntil('\n');
    s.trim();
    String op = "";
    digitalWrite(SS_PIN,LOW);
    delay(10);
    SPI.transfer(s[0]);
    for (int i=1; i < s.length(); i++){
      char received = SPI.transfer(s[i]);
      op = op + received;
    }
    op = op + char(SPI.transfer(0));
    digitalWrite(SS_PIN,HIGH);
    Serial.print("Received:");
    Serial.println(op);
    delay(100);
  }
}
