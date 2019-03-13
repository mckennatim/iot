#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h> 
#endif
#include <PubSubClient.h>

#include "config.h"
#include "STATE.h"
#include "MQclient.h" //globals(extern) NEW_MAIL, itopic, ipayload + Console + handleCallback()

// void getOnline();
char mqsettings[354] ="{\"devid\":\"CYURD011\",\"owner\":\"tim@sitebuilt.net\",\"pwd\":\"geniot\",\"mqtt_server\":\"sitebuilt.net\",\"mqtt_port\":\"1883\",\"sensor_type\":\"dht\"}";
// char mqsettings[354] =MQ_SETTINGS;
WiFiClient espClient;
PubSubClient client(espClient);
MQclient mq(devid, owner, pwd);

void setup() {
  Serial.begin(115200);
  Serial.println(mqsettings);
  getOnline();
  saveConfig();
  delay(2000);
  readConfig();
  client.setServer(mqtt_server, atoi(mqtt_port));
  client.setCallback(handleCallback); //in Req.cpp
  //reconfig(mqsettings);
}

void loop() {
  if(!client.connected()){
    Serial.println(owner);
    mq.reconn(client);
  }else{
    
    client.loop();
  }   
}