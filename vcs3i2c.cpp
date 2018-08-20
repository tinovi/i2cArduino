/*
 * vcs3i2c.cpp
 *
 */
#include "vcs3i2c.h"
#include "Wire.h"

int addr=0x63;
int initLib(int address){
  addr = address;
  Wire.begin();
}


byte getState(){ //-1:no data, 0:err, 1:ok
  Wire.requestFrom(addr, 1, false);
  if(Wire.available()>0){
    return Wire.read();
  }else{
    return -1;
  }
}

int16_t getVal(byte reg){

  Wire.beginTransmission(addr); // transmit to device
  Wire.write(reg);              // sends one byte
  Wire.endTransmission();    // stop transmitting
 
  Wire.requestFrom(addr, 2, false);
  int16_t ret=0;
  if(Wire.available()>1){
    byte *pointer = (byte *)&ret;
    pointer[0] = Wire.read();
    pointer[1] = Wire.read();
  }
  return ret;
}


byte setReg8(byte reg, byte val){
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(reg);              // sends one byte
  Wire.write(val);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  return getState();
}

byte setReg(byte reg){
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(reg);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  return getState();
}



int calibrationAir(){
  return setReg(REG_CALIBRATE_AIR);
}

int calibrationWater(){
  return setReg(REG_CALIBRATE_WATER);
}

int calibrationEC(int16_t valueUs)
{
  Wire.beginTransmission(addr); 
  Wire.write(REG_CALIBRATE_EC);
  uint8_t *pointer = (uint8_t *)&valueUs;
  Wire.write((uint8_t *)&pointer[0],1);
  Wire.write((uint8_t *)&pointer[1],1);
  Wire.endTransmission(); 
  return getState();
  
}
int newAddress(byte newAddr){
  return setReg8(REG_SET_I2C_ADDR, newAddr);
}

int newReading(){
  return setReg(REG_READ_START);
}

float getE25()
{
  return getVal(REG_READ_E25)/100;
}

float getEC()
{
  return getVal(REG_READ_EC)/100;
}

float getTemp()
{
  return getVal(REG_READ_TEMP)/100;
}

float getVWC()
{
  return getVal(REG_READ_VWC);
}

void getData(float readings[]){
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(REG_GET_DATA);              // sends one byte
  Wire.endTransmission();    // stop transmitting
 Wire.requestFrom(addr, 8, false);
  int ar = 0;
  while(Wire.available()>1){
    int16_t ret;
    byte *pointer = (byte *)&ret;
    pointer[0] = Wire.read();
    pointer[1] = Wire.read();
    if(ar<3){
      readings[ar]=ret/100;
    }else{
      readings[ar]=ret;
     }
    ar++;
  }
}

