#include "i2cArduino.h"

SVCS3 vcs;

void setup() {
   Serial.begin(115200);
  vcs.init(0x63);
}

void loop() {
  vcs.newReading(); // start sensor reading
  delay(100); //let sensor read data

//getting values one by one
  float e25 = vcs.getE25();
  float ec = vcs.getEC();
  float temp = vcs.getTemp();
  float vwc = vcs.getVWC();
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

//getting values all at one request
  float dat[4]={0,0,0,0};
  vcs.getData(dat);
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
