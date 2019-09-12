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

// void getOnline();
char mqsettings[354] ="{\"devid\":\"CYURD011\",\"owner\":\"tim@sitebuilt.net\",\"pwd\":\"geniot\",\"mqtt_server\":\"sitebuilt.net\",\"mqtt_port\":\"1883\",\"sensor_type\":\"dht\"}";
// char mqsettings[354] =MQ_SETTINGS;
WiFiClient espClient;
PubSubClient client(espClient);
MQclient mq(devid, owner, pwd);

void Repeats(){
  Serial.println("15 second timer");         
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

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
  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  Alarm.timerRepeat(15, Repeats);  
}

void loop() {
  if(!client.connected()){
    Serial.println(owner);
    mq.reconn(client);
  }else{
    
    client.loop();
  }
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display   
}