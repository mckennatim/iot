#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h> 
#endif
#include <PubSubClient.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

#include "config.h"
#include "STATE.h"
#include "MQclient.h" //globals(extern) NEW_MAIL, itopic, ipayload + Console + handleCallback()

char mqsettings[354] ="{\"devid\":\"CYURD011\",\"owner\":\"tim@sitebuilt.net\",\"pwd\":\"geniot\",\"mqtt_server\":\"sitebuilt.net\",\"mqtt_port\":\"1883\",\"sensor_type\":\"dht\"}";

WiFiClient espClient;
PubSubClient client(espClient);
MQclient mq(devid, owner, pwd);

void getTime(){
  char* dd = "the time is being requested";
  Serial.println(dd);
  char time[20];
  strcpy(time,devid);
  strcat(time,"/time");  
  client.publish(time, dd, true);   
}

void dailyAlarm(){
  Serial.println("in daily alarm");
  Serial.println(devid);
  int minu = (10*((int)devid[6]-'0')+(int)devid[7]-'0')%16;
  Serial.print(hour());
  Serial.print(':');
  Serial.println(minute());
  Alarm.alarmRepeat(0,minu,0, getTime);
}

void setup() {
  Serial.begin(115200);
  getOnline();
  client.setServer(mqtt_server, atoi(mqtt_port));
  client.setCallback(handleCallback); //in Req.cpp
  Alarm.timerOnce(10, dailyAlarm);
}

void loop() {
  if(!client.connected()){
    Serial.println(owner);
    mq.reconn(client);
  }else{
    
    client.loop();
  }   
}