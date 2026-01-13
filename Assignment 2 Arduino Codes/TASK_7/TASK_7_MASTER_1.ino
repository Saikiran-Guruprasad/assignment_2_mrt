#include <Wire.h>

int a = 0, b = 0;
int sum_ab = 0;
bool waitingForM2 = false;
bool readyToBroadcast = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  if (!waitingForM2 && !readyToBroadcast) {
    Wire.requestFrom(0x06, 1);
    if (Wire.available()) {
      a = Wire.read();
      Serial.print("Received a = ");
      Serial.println(a);
    }
    delay(50);

    Wire.requestFrom(0x07, 1);
    if (Wire.available()) {
      b = Wire.read();
      Serial.print("Received b = ");
      Serial.println(b);
    }
    delay(50);

    sum_ab = a + b;
    Serial.print("Computed (a+b) = ");
    Serial.println(sum_ab);

    Wire.beginTransmission(0x05);
    Wire.write(1);
    Wire.endTransmission();
    delay(100);

    Wire.end();
    Wire.begin(0x04);
    Wire.onReceive(receiveFromM2);
    waitingForM2 = true;
  }

  if (readyToBroadcast) {
    Wire.end();
    Wire.begin();
    delay(50);

    Wire.beginTransmission(0x00);
    Wire.write(sum_ab);
    Wire.endTransmission();
    delay(100);

    Wire.end();
    delay(100);
    Wire.begin();

    waitingForM2 = false;
    readyToBroadcast = false;

    delay(5000);
  }

  delay(10);
}

void receiveFromM2(int numBytes) {
  while (Wire.available()) {
    Wire.read();
  }
  readyToBroadcast = true;
}
