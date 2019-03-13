// #if defined(ESP8266)
// #include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
// #else
// #include <WiFi.h>          //https://github.com/esp8266/Arduino
// #endif

// //needed for library
// #include <DNSServer.h>
// #if defined(ESP8266)
// #include <ESP8266WebServer.h>
// #else
// #include <WebServer.h>
// #endif
// #include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
// #include <Arduino.h>
#include "config.h"

// void getOnline();
char mqsettings[354] ="{\"devid\":\"CYURD011\",\"owner\":\"tim@sitebuilt.net\",\"pwd\":\"geniot\",\"mqtt_server\":\"sitebuilt.net\",\"mqtt_port\":\"1883\",\"sensor_type\":\"dht\"}";
// char mqsettings[354] =MQ_SETTINGS;

void setup() {
  Serial.begin(115200);
  Serial.println(mqsettings);
  getOnline();
  saveConfig();
  delay(2000);
  readConfig();
  //reconfig(mqsettings);
}

void loop() {
}