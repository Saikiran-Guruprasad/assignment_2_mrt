#include <SPI.h>

volatile int x = 0;
volatile bool sending = false;

void setup() {
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

ISR(SPI_STC_vect) {
  char c = SPDR;
  if (!sending) {
    if (c == '\n') {
      x = x - 1;         
      sending = true;     
    } else {
      x = x * 10 + (c - '0');
    }
    SPDR = 0;
  }
  else {
    SPDR = char((x % 10) + '0');
    x /= 10;

    if (x == 0) {
      sending = false;
    }
  }
}

void loop(){
}