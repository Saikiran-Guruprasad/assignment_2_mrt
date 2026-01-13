#include <Wire.h>

int c = 0, d = 0;
int sum_cd = 0;
bool shouldAcquireBus = false;
bool readyToBroadcast = false;

void setup() {
  Wire.begin(0x05);
  Wire.onReceive(receiveFromM1);
  Serial.begin(9600);
}

void loop() {
  if (shouldAcquireBus) {
    Wire.end();
    Wire.begin();
    delay(50);

    Wire.requestFrom(0x06, 1);
    if (Wire.available()) {
      c = Wire.read();
      Serial.print("Received c = ");
      Serial.println(c);
    }
    delay(50);

    Wire.requestFrom(0x07, 1);
    if (Wire.available()) {
      d = Wire.read();
      Serial.print("Received d = ");
      Serial.println(d);
    }
    delay(50);

    sum_cd = c + d;
    Serial.print("Computed (c+d) = ");
    Serial.println(sum_cd);

    Wire.beginTransmission(0x04);
    Wire.write(1);
    Wire.endTransmission();
    delay(100);

    Wire.end();
    Wire.begin(0x05);
    Wire.onReceive(receiveBroadcast);

    shouldAcquireBus = false;
    readyToBroadcast = true;
  }

  delay(10);
}

void receiveFromM1(int numBytes) {
  if (!readyToBroadcast) {
    while (Wire.available()) {
      Wire.read();
    }
    shouldAcquireBus = true;
  }
}

void receiveBroadcast(int numBytes) {
  if (readyToBroadcast && Wire.available()) {
    Wire.read();
    Wire.end();
    Wire.begin();
    delay(50);
    Wire.beginTransmission(0x00);
    Wire.write(sum_cd);
    Wire.endTransmission();
    delay(100);

    Wire.end();
    Wire.begin(0x05);
    Wire.onReceive(receiveFromM1);
    readyToBroadcast = false;
  }
}
