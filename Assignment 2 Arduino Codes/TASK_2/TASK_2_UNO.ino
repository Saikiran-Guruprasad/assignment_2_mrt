#include<SoftwareSerial.h> 
SoftwareSerial Serial1(2,3); 
const int c=2; 

void setup(){ 
  Serial.begin(9600); 
  Serial1.begin(9600); 
  Serial.println("Enter a number x:"); 
} 

void loop(){ 
  static int x=0; 
  while (Serial.available()>0){ 
    char d = Serial.read(); 
    if (d=='\n'){ 
      Serial1.println(x+c); 
      x=0; 
    } 
    else if (d!='\r'){ 
      x=x*10+(d-'0'); 
    } 
  } 
  static int op=0; 
  while(Serial1.available()){ 
    char e = Serial1.read(); 
    if (e=='\n'){ 
      Serial.println(op); 
      op=0; 
    } 
    else if (e!='\r'){ 
      op=op*10+(e-'0'); 
    } 
  } 
}
