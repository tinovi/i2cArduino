#include "vcs3i2c.h"


void setup() {
   Serial.begin(115200);
  initLib(0x63);
}

void loop() {
  newReading(); // start sensor reading
  delay(30); //let sensor read data
  float e25 = getE25();
  float ec = getEC();
  float temp = getTemp();
  float vwc = getVWC();
//    Serial.print("e25");
//    Serial.print("=");
//    Serial.println(e25);
//    Serial.print("ec");
//    Serial.print("=");
//    Serial.println(ec);
//    Serial.print("temp");
//    Serial.print("=");
//    Serial.println(temp);
//    Serial.print("vwc");
//    Serial.print("=");
//    Serial.println(vwc);
  float dat[4]={0,0,0,0};
  getData(dat);
  Serial.println("-----");
    Serial.print("e25");
    Serial.print("=");
    Serial.println(dat[0]);
    Serial.print("ec");
    Serial.print("=");
    Serial.println(dat[1]);
    Serial.print("temp");
    Serial.print("=");
    Serial.println(dat[2]);
    Serial.print("vwc");
    Serial.print("=");
    Serial.println(dat[3]);
  delay(1000);
} 
