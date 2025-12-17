#include<SoftwareSerial.h>

SoftwareSerial Serial1(2,3);

void setup(){
  Serial1.begin(9600);
}

void loop(){
  static int x=0;
  while (Serial1.available()>0){
    char d = Serial1.read();
    if (d=='\n'){
      int op = x*x;
      Serial1.println(op);
      x=0;
    }
    else if (d!='\r'){
      x=x*10+(d-'0');
    }
  }
}