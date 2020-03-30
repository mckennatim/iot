## resources

https://tttapa.github.io/ESP8266/Chap04%20-%20Microcontroller.html

https://steve.fi/hardware/d1-pins/

## tips
* printf doesn't always print , use Serail.println
* constant values you need access too in multiple files are best declared in a .h file ex: `struct sen_t { .... };, extern const sent_t SE;` then intialized or set in a .cpp file  ex: `const labels_t la {
  {"devtime", "cmd"},2};` 
## weird shit
* in main you have to have `Sched sched;` even though there is no use of that class in main. (req.processInc does use Sched, declaring it in Reqs is not enough) else you get

      undefined reference to `sched'
      collect2.exe: error: ld returned 1 exit status
      *** [.pio\build\d1_mini\firmware.elf] Error 1

## log

### 3/29/20 07-multisensor-pubState
All sensors except max31855 working and publishing

### 3/28/20 05-multisensor-CONFIG
constant values you need access too in multiple files are best declared in a .h file ex: `struct sen_t { .... };, extern const sent_t SE;` then intialized or set in a .cpp file  ex: `const labels_t la {
  {"devtime", "cmd"},2};`

TODO - publish from the device, the current state of the sensors. PROBLEM - App is used to seeing state data from sensors with [64, 0, 68,59] even if there is no hilimit or lolimit or state.


### 3/27/20 04-multisensor-processInc_devtime
SOFAR - Added enough of `Regs.h` and `Reqs.cpp`  ans `Sched.h` and `Sched.cpp` to allow it to process incoming devtime request and set the device. THIS IS WHERE `ArduinoJson` starts to get used but left it at version 5.14.0.

Incorporated a couple of Sched member functions to respond to the handleCallback function that mqtt uses when something comes in. When something does come in the raw data is put into itopic and ipayload and then the NEW_MAIL flag is set. The main loop picks up the flag and processesIn(oming) message wheter it be {"devtime", "cmd", "prg", "req", "set", "progs"} and sched.actTime()case 0 is devtime which calls sched.deseriTime() 

weird shit: 

### 3/25/20 03-multisensor-MAX31855
SOFAR - Cannot get MAX31855 to work as sensor. Probably problem with the board

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
SOFAR - Moved light code to multsensors and added some sensors as well as `MQclient.h` and `MQclient.cpp` and added db entries so the device could connect to the mqtt broker. `MQclient.cpp` makes a proper request to the broker for the proper time and the broker hears it.

* CONST.h to set up a device. trying to allow processing of input by stepping through arrays
* Leaving build flags D in platfromio.ini
* mq works but maybe should not be sticking with ArduinoJSON 5.13 as I move on
* sensors working so far 
    * BH1750 light sensor. Light sensor id sn i2c device. 
    * DS18B20 onewire temp sensor. Can have multiple banks of multiple sensors
    * DHT11/22 remember dht.begin()
    * hygrometer uses analog A0 constrain and map

### 3/21/20 00-light+config
SOFAR - Added `config.h` and `config.c` to run the code to connect to WIFI

### 3/20/20 00-light
SOFAR - just sensors working without internet using a new `CONST.h` as a config file, now being able to iterate through it in `redSensors()`

^REBUILDING THE CODEBASE^