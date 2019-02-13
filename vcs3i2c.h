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
  //pass i2c addres of sensor, default 0x63
  int init(int address);
  // update i2c address of sesnor
  int newAddress(byte newAddr);
  // hold sesnor in air or put in dry soil and call  (offset DP = 1 or VWC=0%)
  int calibrationAir();
  // submerge sesnor in the water or soil with water (offset DP = 80 or VWC=100%)
  int calibrationWater();
  // submerge sesnor in EC calibration fluid or soil with known EC and supply correc EC vaue in 
  int calibrationEC(int16_t valueUs);
  //initate reading, then need to wait for 100ms to let reading to finish
  int newReading();
  float getE25();
  float getEC();
  float getTemp();
  float getVWC();
  //get all values, supply float[4] , return 0-DP;1-EC;2-Temp;3-VWC
  void getData(float retVal[]);
private:
  int addr;
  int getState();
  int16_t getVal(byte reg);
  int setReg8(byte reg, byte val);
  int setReg(byte reg);


};

#endif /* VCS3I2C_H_ */

