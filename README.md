# Tinovi PM-WCS-3-I2C soil moisture / EC and Temperature i2c sensor Arduino library

## Interfacing from Arduino
**WARNING!!! use 3.3 voltage levels only, more voltage will damage device, latest models support 2.2v-5v voltage levels**


###wiring to Arduiono:

Arduiono pin #3V3 - sensor red (2.8v-5v)

Arduiono pin #A4 - sensor green (SDA)

Arduiono pin #A5 - sensor white (SCL)

Arduiono pin #GND - sensor black (GND)

pin #GND - shield (GND)

**SDA and SCL lines requires pull-up resitors to 3.3v line, we recommend to use 1.8K resistors, because of long wiring to i2c sensor.**

### API
```
LeafSens();
  //pass i2c addres of sensor, default 0x61
  int init(int address);
  // update i2c address of sesnor
  int newAddress(byte newAddr);
  // hold sesnor in air or put in dry soil and call  (offset Wet=0%)
  int calibrationAir();
  // submerge sesnor in the water or soil with water (offset Wet = 100%)
  int calibrationWater();
  //initate reading, then need to wait for 100ms to let reading to finish
  int newReading();
  float getWet();
  float getTemp();
  //get all values, supply float[2] , return 0-Wet;1-Temp
  void getData(float retVal[]);
```



## Interfacing from Raspberry Pi

**WARNING!!! 3.3 voltage levels only, more voltage will damage device**


###wiring to Raspberry Pi connector:

Raspberry Pi pin #1 - sensor red (3.3v)

Raspberry Pi pin #3 - sensor green (SDA)

Raspberry Pi pin #5 - sensor white (SCL)

Raspberry Pi pin #9 - sensor black (GND)

Raspberry Pi pin #9 - sensor shield(GND)

### Enable i2c interface in Raspberry Pi

see [this manual](https://learn.sparkfun.com/tutorials/raspberry-pi-spi-and-i2c-tutorial)


### Get software
This sample software demonstrates hot to make command line interface for the sensor.
Sensor default I2C address is 0x61.

To get software execute following on Raspberry Pi:

`git clone https://github.com/tinovi/i2cRaspberry`

`cd i2cRaspberry`

`chmod 777 *.sh` to add for scripts execute permission

`./mk.sh` to make demo executable

`./read.sh` to read data from sensor

`./svcs 0x61 addr 0x65` to change default address 0x61 to new I2C address: 0x65




### Get software

This sample software demonstrates hot to read data from sensor.

Sensor default I2C address is 0x61.

Download Arduino library from [there.](https://github.com/tinovi/LeafArduinoI2c)

<a href="https://tinovi.com/tinovi-shop/"> Shop </a>

