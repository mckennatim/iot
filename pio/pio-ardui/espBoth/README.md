## resources

https://tttapa.github.io/ESP8266/Chap04%20-%20Microcontroller.html

https://steve.fi/hardware/d1-pins/

## tips
* printf doesn't always pring , use Serail.println

## log

### 3/27/20 04-multisensor-processInc_devtime
Incorporated a couple of Sched member functions to respond to the handleCallback function that mqtt uses when something comes in. When something does come in the raw data is put into itopic and ipayload and then the NEW_MAIL flag is set. The main loop picks up the flag and processesIn(oming) message wheter it be {"devtime", "cmd", "prg", "req", "set", "progs"} and sched.actTime()case 0 is devtime which calls sched.deseriTime() 

### 3/25/20 03-multisensor-MAX31855

DOES NOT WORK

The SPI Interface uses 4 lines for data exchange:

* SCLK-Serial Clock: Clock signal (from lead) Ot
her designations: SCK, CLK
* MOSI-Master Output, Slave Input: Data from leading to Vedomo
mudrugie notation: SDI, DI, SI
* MISO — Master Input, Slave Output: Data from the Vedushhemudrug
ie-driven notation: SDO, do, SO
* SS-Slave Select: Slave selection; is established by the
Other designations: nCS, CS, CSB, CSN, nSS, STE

MAX 31855 still not working  (probably board problem not SPI) though Nokia 5110 SPI display does (in test)

* CLK - > D5(14)SCK
* CS  ->  D8(15)SS
* D0  ->  D6(12)MISO
### 3/24/20 02-multisensor-mq

* CONST.h to set up a device. trying to allow processing of input by stepping through arrays
* Leaving build flags D in platfromio.ini
* mq works but maybe should not be sticking with ArduinoJSON 5.13 as I move on
* sensors working so far 
    * BH1750 light sensor. Light sensor id sn i2c device. 
    * DS18B20 onewire temp sensor. Can have multiple banks of multiple sensors
    * DHT11/22 remember dht.begin()
    * hygrometer uses analog A0 constrain and map