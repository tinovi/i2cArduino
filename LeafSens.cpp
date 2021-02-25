/*
 * i2cArduino.cpp
 *
 */
#include "LeafSens.h"


LeafSens::LeafSens(){
  addr=ADDR;
}

int LeafSens::init(int address, TwoWire *the_wire){
  _wire = the_wire;
  addr = address;
  return 0;
}

int LeafSens::init(int address){
  _wire = &Wire;
  _wire->begin();
  addr = address;
  return 0;
}


bool LeafSens::i2cdelay(int size){
  int i=0;
  for (;_wire->available() < size && i<=size;i++) {
	  delay(2);
  }
  if(i>=size){
	  return false;
  }else{
	  return true;
  }
}

int LeafSens::getState(){ //-1:no data, 0:err, 1:ok
  _wire->requestFrom(addr, (uint8_t)1);
   if(i2cdelay(1)){
    return _wire->read();
  }else{
    return -1;
  }
}

int16_t LeafSens::getVal(byte reg){

  _wire->beginTransmission(addr); // transmit to device
  _wire->write(reg);              // sends one byte
  _wire->endTransmission();    // stop transmitting
 
  _wire->requestFrom(addr, (uint8_t)2);
  int16_t ret=0;
  if(i2cdelay(2)){
	byte *pointer = (byte *)&ret;
    pointer[0] = _wire->read();
    pointer[1] = _wire->read();
  }
  return ret;
}

uint32_t LeafSens::getVal32(byte reg){

  _wire->beginTransmission(addr); // transmit to device
  _wire->write(reg);              // sends one byte
  _wire->endTransmission();    // stop transmitting

  _wire->requestFrom(addr, (uint8_t)4);
  int16_t ret=0;
  if(i2cdelay(4)){
	byte *pointer = (byte *)&ret;
    pointer[0] = _wire->read();
    pointer[1] = _wire->read();
    pointer[2] = _wire->read();
    pointer[3] = _wire->read();
  }
  return ret;
}


int LeafSens::setReg8(byte reg, byte val){
  _wire->beginTransmission(addr); // transmit to device
  _wire->write(reg);              // sends one byte
  _wire->write(val);              // sends one byte
  _wire->endTransmission();    // stop transmitting
  return getState();
}

int LeafSens::setReg(byte reg){
  _wire->beginTransmission(addr); // transmit to device
  _wire->write(reg);              // sends one byte
  _wire->endTransmission();    // stop transmitting
  delay(2);
  return getState();
}


int LeafSens::resetDefault(){
  return setReg(REG_RES);
}


int LeafSens::calibrationAir(){
  return setReg(REG_AIR);
}

int LeafSens::calibrationWater(){
  return setReg(REG_WATER);
}
int LeafSens::newAddress(byte newAddr){
  if(setReg8(REG_ADDR, newAddr)){
    addr = newAddr;
  }
  else{
    return 0;
  }
  return 1;
}

int LeafSens::newReading(){
  _wire->beginTransmission(addr); // transmit to device
  _wire->write(REG_READ);              // sends one byte
  _wire->endTransmission();    // stop transmitting
  delay(300);
  return getState();
}

float LeafSens::getWet()
{
  return getVal(REG_WET)/100.0;
}

float LeafSens::getTemp()
{
  return getVal(REG_TEMP)/100.0;
}

int16_t LeafSens::getCap()
{
  return getVal(REG_CAP);
}


uint32_t  LeafSens::getRt(){
	return getVal32(REG_RT);
}

void LeafSens::getData(float readings[]){
  _wire->beginTransmission(addr); // transmit to device
  _wire->write(REG_READ);              // sends one byte
  _wire->endTransmission();    // stop transmitting
  _wire->requestFrom(addr, (uint8_t)8);
  if(i2cdelay(8)){
	  for (int k = 0; k < 2; k++){
		  int16_t ret;
		  byte *pointer = (byte *)&ret;
		  pointer[0] = _wire->read();
		  pointer[1] = _wire->read();
		  switch (k) {
        case 0:
          readings[k] = ret / 100.0;
          break;
        case 1:
          readings[k] = ret / 100.0;
          break;
      }
	  }
  }else{
	  for (int k = 0; k < 2; k++){
		readings[k] = 0.0;
	  }
  }
}

void LeafSens::getRaw(byte data[]){
  _wire->beginTransmission(addr); // transmit to device
  _wire->write(REG_DATA);              // sends one byte
  _wire->endTransmission();    // stop transmitting
  _wire->requestFrom(addr, (uint8_t)8);
  if(i2cdelay(8)){
	  for(int i = 0; i<8; i++){
		  data[i] = _wire->read();
	  }
  }else{
	  for(int i = 0; i<8; i++){
		  data[i] = 0;
	  }
  }
}
