#include <Wire.h>

void setup(){
  Wire.begin();      
  Serial.begin(9600); 
} 

void loop(){
  int a,b;
  Wire.requestFrom(4, 1);   
  if (Wire.available()){
    a = Wire.read();
  }
  Wire.requestFrom(5,1); 
  if (Wire.available()){
    b = Wire.read();
  }
  Serial.println((a+b)*(a+b));
  delay(500);
}
