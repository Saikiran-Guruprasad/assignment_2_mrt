#include <Wire.h>

int b = 2;
int d = 4;
bool sendb = true;
int values[4] = {0,0,0,0};
int op = 0;

void setup(){
  Serial.begin(9600);
  Wire.begin(7);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop(){
  delay(10);
}

void requestEvent(){
  if (sendb){
    Wire.write(b);
    values[1] = b;
    sendb = false;
  } 
  else{
    Wire.write(d);
    values[3] = d;
    sendb = true;
  }
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    int data = Wire.read();
    op++;
    
    if (op == 1) {
      int sumab = data;
      values[0] = sumab - values[1];
    } 
    else if (op == 2) {
      int sumcd = data;
      values[2] = sumcd - values[3];
      Serial.println(values[0]);
      Serial.println(values[1]);
      Serial.println(values[2]);
      Serial.println(values[3]);
      op = 0;
    }
  }
}