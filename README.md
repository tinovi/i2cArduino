


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


## Interfacing from Arduino
**WARNING!!! use 3.3 voltage levels only, more voltage will damage device**

###wiring to Arduiono:

Arduiono pin #3V3 - sensor red (3.3v)

Arduiono pin #A4 - sensor green (SDA)

Arduiono pin #A5 - sensor white (SCL)

Arduiono pin #GND - sensor black (GND)

pin #GND - shield (GND)

**SDA and SCL lines requires pull-up resitors to 3.3v line, we recommend to use 1.8K resistors, because of long wiring to i2c sensor.**

### Get software

This sample software demonstrates hot to read data from sensor.

Sensor default I2C address is 0x63.

Download Arduino library from [there.](https://github.com/tinovi/i2cArduino)

<a href="https://www.tindie.com/stores/tinovi/"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-mediums.png" alt="I sell on Tindie" width="150" height="78" /></a>
