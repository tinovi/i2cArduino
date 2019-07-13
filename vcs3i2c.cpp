/*
 * vcs3i2c.cpp
 *
 */
#include "vcs3i2c.h"


SVCS3::SVCS3(){
  addr=0x63;
}

int SVCS3::init(int address){
  addr = address;
  Wire.begin();
}


int SVCS3::getState(){ //-1:no data, 0:err, 1:ok
  Wire.requestFrom(addr, 1);
  if(Wire.available()>0){
    return Wire.read();
  }else{
    return -1;
  }
}

int16_t SVCS3::getVal(byte reg){

  Wire.beginTransmission(addr); // transmit to device
  Wire.write(reg);              // sends one byte
  Wire.endTransmission();    // stop transmitting
 
  Wire.requestFrom(addr, 2);
  int16_t ret=0;
  if(Wire.available()>1){
    byte *pointer = (byte *)&ret;
    pointer[0] = Wire.read();
    pointer[1] = Wire.read();
  }
  return ret;
}


int SVCS3::setReg8(byte reg, byte val){
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(reg);              // sends one byte
  Wire.write(val);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  return getState();
}

int SVCS3::setReg(byte reg){
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(reg);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  return getState();
}



int SVCS3::calibrationAir(){
  return setReg(REG_CALIBRATE_AIR);
}

int SVCS3::calibrationWater(){
  return setReg(REG_CALIBRATE_WATER);
}

int SVCS3::calibrationEC(int16_t valueUs)
{
  Wire.beginTransmission(addr); 
  Wire.write(REG_CALIBRATE_EC);
  uint8_t *pointer = (uint8_t *)&valueUs;
  Wire.write((uint8_t *)&pointer[0],1);
  Wire.write((uint8_t *)&pointer[1],1);
  Wire.endTransmission(); 
  return getState();
  
}
int SVCS3::newAddress(byte newAddr){
  if(setReg8(REG_SET_I2C_ADDR, newAddr)){
    addr = newAddr;
  }
  else{
    return 0;
  }
  return 1;
}

int SVCS3::newReading(){
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(REG_READ_START);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(300);
  return getState();
}

float SVCS3::getE25()
{
  return getVal(REG_READ_E25)/100.0;
}

float SVCS3::getEC()
{
  return getVal(REG_READ_EC)/10.0;
}

float SVCS3::getTemp()
{
  return getVal(REG_READ_TEMP)/100.0;
}

float SVCS3::getVWC()
{
  return getVal(REG_READ_VWC)/10.0;
}

void SVCS3::getData(float readings[]){
  Wire.beginTransmission(addr); // transmit to device
  Wire.write(REG_GET_DATA);              // sends one byte
  Wire.endTransmission();    // stop transmitting
 Wire.requestFrom(addr, 8);
  int ar = 0;
  while(Wire.available()>1){
    int16_t ret;
    byte *pointer = (byte *)&ret;
    pointer[0] = Wire.read();
    pointer[1] = Wire.read();
	switch (ar) {
	case 0:
		readings[ar] = ret / 100.0;
		break;
	case 1:
		readings[ar] = ret / 10.0;
		break;
	case 2:
		readings[ar] = ret / 100.0;
		break;
	case 3:
		readings[ar] = ret / 10.0;
		break;
	}
	ar++;
  }
}


