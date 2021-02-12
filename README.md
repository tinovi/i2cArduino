# Tinovi PM-WCS-3-I2C soil moisture / EC and Temperature i2c sensor Arduino library

## Interfacing from Arduino
**WARNING!!! use 3.3 voltage levels only, more voltage will damage device, latest models support 2.2v-5v voltage levels**


###wiring to Arduiono:

Arduiono pin #3V3 - sensor red (3.3v) (2.2v-5 for latest version)

Arduiono pin #A4 - sensor green (SDA)

Arduiono pin #A5 - sensor white (SCL)

Arduiono pin #GND - sensor black (GND)

pin #GND - shield (GND)

**SDA and SCL lines requires pull-up resitors to 3.3v line, we recommend to use 1.8K resistors, because of long wiring to i2c sensor.**

### API
```
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
Sensor default I2C address is 0x63.

To get software execute following on Raspberry Pi:

`git clone https://github.com/tinovi/i2cRaspberry`

`cd i2cRaspberry`

`chmod 777 *.sh` to add for scripts execute permission

`./mk.sh` to make demo executable

`./read.sh` to read data from sensor

`./svcs 0x63 addr 0x65` to change default address 0x63 to new I2C address: 0x65




### Get software

This sample software demonstrates hot to read data from sensor.

Sensor default I2C address is 0x63.

Download Arduino library from [there.](https://github.com/tinovi/i2cArduino)

Download Arduino esp32 library from [there.](https://github.com/tinovi/i2cArduino/tree/esp32)

<a href="https://tinovi.com/wp-content/uploads/2020/01/PM-WCS-3-I2C.pdf"> PM-WCS-3-I2C.pdf </a>

<a href="https://tinovi.com/tinovi-shop/"> Shop </a>

[PM-WCS-3-I2C] https://github.com/tinovi/i2cArduino/blob/master/i2c-alvas-EC-729x1024.png "PM-WCS-3-I2C"
