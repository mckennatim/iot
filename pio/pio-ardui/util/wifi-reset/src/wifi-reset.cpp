#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>          //https://github.com/esp8266/Arduino
#endif

//needed for library
#include <DNSServer.h>
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


void setup() {
    Serial.begin(115200);
    WiFiManager wifiManager;
    //reset saved settings forces AP
    // wifiManager.resetSettings();
    // wifiManager.autoConnect("EspAP");
    // Serial.println("connected...yeey :)");
    WiFi.disconnect();
}

void loop() {
    // put your main code here, to run repeatedly:
    
}