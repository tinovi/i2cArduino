/*
 * vcs3i2c.h
 *
 */

#ifndef VCS3I2C_H_
#define VCS3I2C_H_

#include <Arduino.h>
#include <Wire.h>

#define ADDR 0x63

#define  REG_READ_START    0x01
#define  REG_GET_DATA      0x09

#define  REG_READ_E25     0x02
#define  REG_READ_EC      0x03
#define  REG_READ_TEMP    0x04
#define  REG_READ_VWC     0x05

#define  REG_CALIBRATE_AIR    0x06
#define  REG_CALIBRATE_WATER  0x07
#define  REG_CALIBRATE_EC  0x10

#define REG_SET_I2C_ADDR    0x08

class SVCS3
{
public:
  SVCS3();
  int init(int address);
  int newAddress(byte newAddr);
  int calibrationAir();
  int calibrationWater();
  int calibrationEC(int16_t valueUs);
  int newReading();
  float getE25();
  float getEC();
  float getTemp();
  float getVWC();
  void getData(float retVal[]);
private:
  int addr;
  int getState();
  int16_t getVal(byte reg);
  int setReg8(byte reg, byte val);
  int setReg(byte reg);


};

#endif /* VCS3I2C_H_ */

