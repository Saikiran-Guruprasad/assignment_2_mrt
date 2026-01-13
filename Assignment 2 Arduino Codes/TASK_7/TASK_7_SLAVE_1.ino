#include <Wire.h>

int valueForM1 = 2;
int valueForM2 = 4;
int receivedValues[4] = {0, 0, 0, 0};
int broadcastCount = 0;

void setup() {
  Wire.begin(0x06);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

void requestEvent() {
  static bool toggle = true;
  if (toggle) {
    Wire.write(valueForM1);
    toggle = false;
  } else {
    Wire.write(valueForM2);
    toggle = true;
  }
}

void receiveEvent(int numBytes) {
  if (Wire.available()) {
    int value = Wire.read();

    if (broadcastCount == 0) {
      int sum_ab = value;
      receivedValues[0] = valueForM1;
      receivedValues[1] = sum_ab - valueForM1;
      broadcastCount++;
    } else if (broadcastCount == 1) {
      int sum_cd = value;
      receivedValues[2] = valueForM2;
      receivedValues[3] = sum_cd - valueForM2;

      Serial.print("a = ");
      Serial.println(receivedValues[0]);
      Serial.print("b = ");
      Serial.println(receivedValues[1]);
      Serial.print("c = ");
      Serial.println(receivedValues[2]);
      Serial.print("d = ");
      Serial.println(receivedValues[3]);

      broadcastCount = 0;
    }
  }
}
