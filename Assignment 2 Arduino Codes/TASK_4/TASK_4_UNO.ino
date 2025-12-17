#include<SPI.h>

const int SS_PIN_1 = 10;
const int SS_PIN_2 = 9;

void setup(){
  Serial.begin(9600);
  pinMode(SS_PIN_1,OUTPUT);
  pinMode(SS_PIN_2,OUTPUT);
  digitalWrite(SS_PIN_1,HIGH);
  digitalWrite(SS_PIN_2,HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop(){
  if(Serial.available()>0){
    String op="";
    int x=0;
    while (Serial.available()>0){ 
      char d = Serial.read(); 
      if (d=='\n'){  
        break;
      } 
      else if (d!='\r'){ 
        x=x*10+(d-'0');
        op+=d; 
      }
    }
    if(x%2==0){
      digitalWrite(SS_PIN_1,LOW);
      delay(10);
      for (int i=0; i < op.length(); i++){
        SPI.transfer(op[i]);
        delay(5);
      }
      SPI.transfer('\n');
      delay(15);
      digitalWrite(SS_PIN_1,HIGH);
      delay(50);
      digitalWrite(SS_PIN_1,LOW);
      delay(10);
      Serial.print("Received:");
      String op1="";
      for (int i = 0; i < op.length(); i++) {
        char received = SPI.transfer(0);
        op1 += received;
        delay(5);
      }
      digitalWrite(SS_PIN_1,HIGH);
      String reversed = "";
      for (int i = op1.length() - 1; i >= 0; i--) {
        reversed += op1[i];
      }
      Serial.println(reversed);
      delay(100);
    }
    else{
      digitalWrite(SS_PIN_2,LOW);
      delay(10);
      for (int i=0; i < op.length(); i++){
        SPI.transfer(op[i]);
        delay(5);
      }
      SPI.transfer('\n');
      delay(15);
      digitalWrite(SS_PIN_2,HIGH);
      delay(50);
      digitalWrite(SS_PIN_2,LOW);
      delay(10);
      Serial.print("Received:");
      String op2="";
      for (int i = 0; i < op.length(); i++) {
        char received = SPI.transfer(0);
        op2 += received;
        delay(5);
      }
      digitalWrite(SS_PIN_2,HIGH);
      String reversed = "";
      for (int i = op2.length() - 1; i >= 0; i--) {
        reversed += op2[i];
      }
      Serial.println(reversed);
      delay(100);
    }
  }
}
