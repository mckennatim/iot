# platformio

## iot
### log
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