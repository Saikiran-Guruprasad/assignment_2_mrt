#include <Wire.h>

int a = 1;
int c = 3;
bool senda = true;
int values[4] = {0,0,0,0};
int op = 0;

void setup(){
  Serial.begin(9600);
  Wire.begin(6);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop(){
  delay(10);
}

void requestEvent(){
  if (senda){
    Wire.write(a);
    values[0] = a;
    senda = false;
  } 
  else{
    Wire.write(c);
    values[2] = c;
    senda = true;
  }
}

void receiveEvent(int bytes) {
  while (Wire.available()) {
    int data = Wire.read();
    op++;
    
    if (op == 1) {
      int sumab = data;
      values[1] = sumab - values[0];
    } 
    else if (op == 2) {
      int sumcd = data;
      values[3] = sumcd - values[2];
      Serial.println(values[0]);
      Serial.println(values[1]);
      Serial.println(values[2]);
      Serial.println(values[3]);
      op = 0;
    }
  }
}