#include "i2cArduino.h"

LeafSens lcs;

void setup() {
   Serial.begin(115200);
  lcs.init(0x61);
}

void loop() {
  lcs.newReading(); // start sensor reading
  delay(100); //let sensor read data

//getting values one by one
  float wet = lcs.getWet();
  float temp = lcs.getTemp();
//    Serial.print("wet");
//    Serial.print("=");
//    Serial.println(wet);
//    Serial.print("temp");
//    Serial.print("=");
//    Serial.println(temp);

//getting values all at one request
  float dat[2]={0,0};
  lcs.getData(dat);
  Serial.println("-----");
    Serial.print("wet");
    Serial.print("=");
    Serial.println(dat[0]);
    Serial.print("temp");
    Serial.print("=");
    Serial.println(dat[1]);
  delay(1000);
} 
