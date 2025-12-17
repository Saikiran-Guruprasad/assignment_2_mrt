#include <SPI.h> 

volatile char buffer;
volatile bool processed = false;

void setup() {
  pinMode(MISO, OUTPUT);
  
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

ISR (SPI_STC_vect) {
  buffer = SPDR; 
  SPDR = buffer;
}

void loop() {
}