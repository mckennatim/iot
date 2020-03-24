## resources

https://steve.fi/hardware/d1-pins/

## tips

## log

### 3/24/20 02-multisensor-mq

* CONST.h to set up a device. trying to allow processing of input by stepping through arrays
* Leaving build flags D in platfromio.ini
* mq works but maybe should not be sticking with ArduinoJSON 5.13 as I move on
* sensors working so far 
    * BH1750 light sensor
    * DS18B20 onewire temp sensor. Can have multiple banks of multiple sensors
    * DHT11/22 remember dht.begin()
    * hygrometer uses analog A0 constrain and map