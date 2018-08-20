#include "vcs3i2c.h"


void setup() {
  init(ADDR);
}

void loop() {
  newReading(); // start sensor reading
  delay(30); //let sensor read data
  float e25 = getE25();
  float ec = getEC();
  float temp = getTemp();
  float vwc = getVWC();
  delay(1000);
}
