# platformio
platformio.exe run --target upload

* unplug -> replug ->run target upload

platformio.exe device monitor

## questions

hvac stack exception 

ended up being a bad esp8266

but in general... from powershell run 

    PS D:\fs\www\iot\pio\pio-ardui\espBoth\hvac> java -jar EspStackTraceDecoder.jar C:\Users\mcken\.platformio\packages\toolchain-xtensa\bin\xtensa-lx106-elf-addr2line.exe D:\fs\www\iot\pio\pio-ardui\espBoth\hvac\.pio\build\d1_mini\firmware.elf stack.txt

    Exception Cause: 28  [LoadProhibited: A load referenced a page mapped with an attribute that does not permit loads]

    0x402211ec: __fast_strcpy at /home/earle/src/esp-quick-toolchain/repo/newlib/newlib/libc/machine/xtensa/fast_strcpy.S:161
    0x40204461: readConfig() at ??:?
    0x4021c160: WiFiServer::_s_discard(void*, ClientContext*) at ??:?
    0x401057d4: spi_flash_read at ??:?
    0x40213fcf: spiffs_object_find_object_index_header_by_name_v at spiffs_nucleus.cpp:?
    0x40100139: __wrap_spi_flash_read at ??:?
    0x4020e555: EspClass::flashRead(unsigned int, unsigned int*, unsigned int) at ??:?
    0x40211c60: spiffs_hal_read(unsigned int, unsigned int, unsigned char*) at ??:?
    0x40216c81: spiffs_phys_rd at ??:?
    0x40214304: spiffs_page_data_check$isra$3 at spiffs_nucleus.cpp:?
    0x40216714: spiffs_object_read at ??:?
    0x40212a90: malloc at ??:?
    0x40213541: SPIFFS_read at ??:?
    0x4020e768: HardwareSerial::available() at ??:?
    0x4021bb78: fs::File::seek(unsigned int, fs::SeekMode) at ??:?
    0x40204555: getOnline() at ??:?
    0x4021c2b0: WiFiServer::_s_discard(void*, ClientContext*) at ??:?
    0x402045b2: void ArduinoJson::Internals::JsonWriter<fs::File>::writeFloat<float>(float) at ??:?
    0x4021216e: uart_write at ??:?
    0x4020e768: HardwareSerial::available() at ??:?
    0x4020ea79: Print::print(String const&) at ??:?
    0x4020ea79: Print::print(String const&) at ??:?
    0x40100260: digitalWrite at ??:?
    0x40204bdc: readTemps() at ??:?
    0x40204da7: setup at ??:?
    0x402102e4: loop_wrapper() at core_esp8266_main.cpp:?
    0x40100591: cont_wrapper at ??:?   

### How do you set the hysteresis for temp?
 
### What is fCrement? How is it set? 
It sets the time delay for sched.updTimers() and req.pubTimr() in the main loop. It is hard coded in main.cpp `flags_t f` (the 3rd flag)

## recurring problems


### why does the pond timer have such a huge number?
the clock is not getting set. Most often because pin PubSubClient.h the default value of 128 for packet size is not enoung for all the time info. Cange it to 256. (Done in pio-arduino but not arduino1.8.8)

### libraries changing

* Library dependencies should be listed in platformio.ini
* global libraries are in `/c/Users/mcken/.platformio/lib`
* Updating libraries can cause problems
    * PubSubClient (mqtt) in the .h file defaults to packet size of 128. That crashes the app right away since CYURD002/devtime sends back a long string (mainly needed by web apps) Change to 256 in `/c/Users/mcken/.platformio/lib/PubSubClient_ID89/src/PubSubClient.h`
* old code (currently pio-arduino/espBoth/main) requires old ArduinoJson

    lib_deps = 
        DHT sensor library
        Adafruit Unified Sensor
        ArduinoJson@^5.12.0

*  `pio-arduino/espBoth/main-broke` uses ArduinoJson 6. that might have something to do on why it is broke     
    
### won't upload to device

Maybe something else is using yo shit. Hacky solution 

1. unplug device form usb port, replug it in and then quickly...
2. platformio.exe run --target upload

### lotsa problems show in terminal window

Solution `open folder` on one project (platformio.ini) at a time

## iot
### log
### 07-pio-arduino-espBoth-hvac
pio still works. Rolled back to prior ardionoJson

    lib_deps = 
		DHT sensor library
		Adafruit Unified Sensor
		ArduinoJson@^5.12.0 

Created hvac device with 4 temp relays and one timer relay using  ds18b20. First version stack exception and I assumed I made a mistake. Should have then thried the working `main` code, Thought it was old shit on the eeprom (I guess I don't really use the eeprom anymore everything get loaded in build flags in pio )  

BTW see questions above on how to decode stack trace.

#### 06-commands and howtoupload

#### 05-main_espboth-main
Functionality of espWemosiOT/api2/main with esp32 support. ArduinoJson and other libraries are updated.
#### 04-all_4json-fixed_allfiles-in
Repaired all the version 5 problems for AdrduinoJson. Now all files are included and are compiling without errors for d1_mini, wrover and nodemcu-32s
#### 01-xp32-3jsson-spiff-mqconn
Now connects to mqtt
#### 00-init_2json-spiff
Reorganized the directory structure and set up iot. Worked on rebuilding the steps to a fully functioning esp32. Now using ArduinoJson6. At this point both esp32 and esp8266 ...

* gets online using wifimanager
* sets config from build flags
* saves config to a json doc and then serializes it to a config file
* after a delay, reads the config file and puts it in a buffer, prints it then calls reconfig(file buffer)
* reconfig puts the file buffer (or any valid jsonstring) back into json and then copies from json into the (extern) config variables.

This covers all the functionality in spWemosIOT's config.cpp

## setup version2
### 03 try importing the main esp8266 arduin0 project into pio
From pio home select `import arduino project` with board and platform. It will open in some random#-d1_mini folder at the bottom of the files. Now you can use the buttons on the bottom bar to build. When you do you will get errors until the libraries are right but there will be an unsolvable problem. `DHT sensor library` need `Adafruit Unified Sensor` and it confuses pio. You need to add this to your.ini file

    [env:d1_mini]
    platform = espressif8266
    board = d1_mini
    framework = arduino
    monitor_speed = 115200
    lib_deps = 
        DHT sensor library
        Adafruit Unified Sensor

### 02 get blink to run again on esp32
    tim@omen:/d/fs/www/esp-ardui/try/blink$ platformio.exe run --target upload 

or if you want to compile for 2 different platforms you can with something like

    [env:esp wrover kit]
    platform = espressif32
    framework = arduino
    board = esp-wrover-kit
    monitor_speed = 115200
    build_flags =
      -D LED_BUILTIN=22
    upload_port = COM[7]

    [env:d1_mini]
    platform = espressif8266
    board = d1_mini
    framework = arduino
    monitor_speed = 115200
    upload_port = COM[5]

#### com[5] is topleft of pluggable and com[7] is bottom left    

or choose your environment `pio.exe run -t upload -e d1_mini` or `pio.exe run -t upload -e 'esp wrover kit'` or put in a section like this at the top of platformio.ini...

    [platformio]
    env_default = esp wrover kit
### 01 unistall adruino and platformio extensions from vscode and start over

#### how to add a path to $PATH permanently 
you can always `export PATH=$PATH:/newpath` but it doesn't last
* how to run `platfornio.exe from command line? 
1. open mobx, from terminal start unix vscode with `code`, goto tim/.profile 
2. add comething like `PATH="$HOME/bin:$HOME/.local/bin:$PATH:/c/Users/mcken/.platformio/penv/Scripts"`

## setup version 1 esp32
Can make things work from the command line g `platformio.exe run --target  upload` and `platformio.exe device monitor` quicker with more immediate feedback. Going the pio home route described below has too much hysteresis for me. Besides the cli `run` command compiles and loads in one step. To use the examples in  `/d/fs/www/esp-idf/examples` make the following changes; 

1. change the `main` directory to `src`
2. add a `platformio.ini` file.


    ; PlatformIO Project Configuration File
    ;
    ;   Build options: build flags, source filter, extra scripting
    ;   Upload options: custom port, speed and extra flags
    ;   Library options: dependencies, extra library storages
    ;
    ; Please visit documentation for the other options and examples
    ; http://docs.platformio.org/page/projectconf.html
    [env:lolin32]
    platform = espressif32
    board = lolin32
    framework = espidf
    platform = espressif32
    monitor_speed = 115200
    build_flags =
      ; note extra quotes when using strings 
      -D CONFIG_BLINK_GPIO=22
      '-D CONFIG_WIFI_SSID="street_no_vale2"'
      '-D CONFIG_WIFI_PASSWORD="jjjjjjjj"'

You can get the build and uplaod buttons to work if you have opened the project from `pio home` (it has to have a `platformio.ini file` to allow you to open). Otherwise you can use the terminal 

So far I have succeeded with getting_started, system/esp_timer


This directory contains a range of example ESP-IDF projects. These are intended to demonstrate parts of ESP-IDF functionality, and to provide code that you can copy and adapt into your own projects.