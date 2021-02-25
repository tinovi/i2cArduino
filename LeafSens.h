/*
 * vcs3i2c.h
 *
 */

#ifndef VCLL_H_
#define VCLL_H_

#include <Arduino.h>
#include <Wire.h>

#define ADDR 0x61

#define  REG_READ    0x01
#define  REG_TEMP    0x04
#define  REG_WET     0x05

#define  REG_AIR    0x06
#define  REG_WATER  0x07

#define  REG_CAP     0x0A
#define  REG_RES     0x0B
#define  REG_RT     0x0D

#define REG_ADDR 0x08
#define  REG_DATA     0x09

class LeafSens
{
public:
  LeafSens();
  int init(int address, TwoWire *the_wire);
  int init(int address);
  int newAddress(byte newAddr);
  int resetDefault();
  int calibrationAir();
  int calibrationWater();
  int newReading();
  float getWet();
  float getTemp();
  void getData(float retVal[]);
  void getRaw(byte data[]);
  int16_t getCap();
  uint32_t getRt();

private:
  TwoWire *_wire;
  uint8_t addr;
  int getState();
  int16_t getVal(byte reg);
  uint32_t getVal32(byte reg);
  int setReg8(byte reg, byte val);
  int setReg(byte reg);
  bool i2cdelay(int size);

};

#endif /* VCLL_H_ */

