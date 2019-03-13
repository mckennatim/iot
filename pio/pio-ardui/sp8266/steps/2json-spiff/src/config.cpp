#include <FS.h> //must be first
#include <ArduinoJson.h> 

#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h> 
#include "SPIFFS.h"         //https://github.com/esp8266/Arduino
#endif

//needed for library
#include <DNSServer.h>
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "config.h"

//{\"devid\":\"CYURD011\",\"devpwd\":\"geniot\",\"mqtt_server\":\"sitebuilt.net\",\"mqtt_port\":\"1883\",\"node_port\":\"3332\"}
char devid[9]=DEVID;
char owner[254]=OWNER;
char pwd[24]=PWD;
char mqtt_server[60]=MQTT_SERVER;
char mqtt_port[6]=MQTT_PORT;
char sensor_type[24]=SENSOR_TYPE;


void getOnline(){
  WiFiManager wifiManager;
  wifiManager.autoConnect("EspAP");
  Serial.println("connected...yeey :)");
}

void reconfig(char pload[]){
  Serial.println(pload);
  StaticJsonDocument<500> doc;
  auto error = deserializeJson(doc, pload);
  if (error) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return;
  } else {
    serializeJsonPretty(doc, Serial);
    strcpy(devid, doc["devid"]);
    strcpy(owner, doc["owner"]);
    strcpy(pwd, doc["pwd"]);
    strcpy(mqtt_server, doc["mqtt_server"]);
    strcpy(mqtt_port, doc["mqtt_port"]);
    strcpy(sensor_type, doc["sensor_type"]);
  } 
}

void saveConfig(){
  Serial.println("saving config");
  StaticJsonDocument<196> doc;
  doc["devid"] = devid;
  doc["owner"] = owner;
  doc["pwd"] = pwd;
  doc["mqtt_server"] = mqtt_server;
  doc["mqtt_port"] = mqtt_port;
  doc["sensor_type"] = sensor_type;
  if(SPIFFS.begin())
  {
    Serial.println("SPIFFS Initialize....ok");
  }
  else
  {
    Serial.println("SPIFFS Initialization...failed");
  }
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  serializeJson(doc, Serial);
  serializeJson(doc, configFile);
  configFile.close();   
}