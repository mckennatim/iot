#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>
#include "config.h" //getOnline() devid owner pwd
#include "STATE.h"
#include "MQclient.h" //globals(extern) NEW_MAIL, itopic, ipayload + Console + handleCallback()
#include "Reqs.h"
#include "Sched.h"

Sched sched;
ports_t po {4};
flags_t f {0,0,5,0};
state_t sr {{53,0}};
labels_t la; //subsribedTo[], numcmds

DHT dht11(po.sensor, DHT11);

DHT dht22(po.sensor, DHT22);

#define ONE_WIRE_BUS po.sensor 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

BH1750 lightMeter;

WiFiClient espClient;
PubSubClient client(espClient);
Console console(devid, client);
Reqs req(devid, client);
MQclient mq(devid, owner, pwd);

void readSensors(){
  int senseval;
  float lux;
  int thedif;
  int hirng;
  int lorng;
  if(strcmp(sensor_type, "DHT11")==0){
    thedif=1;
    hirng=120;
    lorng=-20;
    senseval = (int)(dht11.readTemperature(true));
  } else if(strcmp(sensor_type, "DHT22")==0){
    thedif=1;
    hirng=120;
    lorng=-20;
    senseval = (int)(dht22.readTemperature(true));
  } else if(strcmp(sensor_type, "hrc")==0){
    thedif=1;
    hirng=120;
    lorng=-20;
    senseval =  digitalRead(po.sensor); 
  } else if(strcmp(sensor_type, "BH1750")==0){
    thedif=100;
    hirng=65535;
    lorng=1;
    senseval = (int)lightMeter.readLightLevel();
  } else if(strcmp(sensor_type, "DS18B20")==0){
    thedif=1;
    hirng=120;
    lorng=-20;
    DS18B20.requestTemperatures(); 
    senseval = (int)DS18B20.getTempFByIndex(0);
  }
  int dif = senseval-sr.sense1.sense;
  if(abs(dif)>thedif && senseval <hirng && senseval>lorng){
    sr.sense1.sense=senseval;
    sr.sense1.rec=1;
    int id = 0;
    int bit =pow(2,id);
    f.HAYsTATEcNG=f.HAYsTATEcNG | bit;
  }
}


void getTime(){
  const char* dd = "the time is being requested";
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

void setup(){
	Serial.begin(115200);
  EEPROM.begin(512);
	Serial.println();
	Serial.println("--------------------------");
  Serial.println("ESP8266 incrbuild");
  Serial.println("--------------------------");
  getOnline();//config.cpp
  client.setServer(mqtt_server, atoi(mqtt_port));
  client.setCallback(handleCallback); //in Req.cpp
  Alarm.timerOnce(10, dailyAlarm);//wait til system time has been requested and set
}

time_t before = 0;
time_t schedcrement = 0;
time_t inow;

void loop(){
  Alarm.delay(100);
  //server.handleClient();
  if(NEW_MAIL){
    req.processInc();
    //Serial.println("hay NEW_MAIL");
    NEW_MAIL=0;
  }  
  if(!client.connected() && !f.fORCErESET){
    Serial.println(owner);
     mq.reconn(client);
  }else{
    client.loop();
  }  
  inow = millis();
  if (inow - before > 1000) {
    before = inow;
    if(f.aUTOMA){
      readSensors();
    }
    if(f.HAYsTATEcNG>0){
      // Serial.print("f.HAYsTATEcNG=");
      // Serial.println(f.HAYsTATEcNG);
      //console.log("example console.log entry");
      req.pubState(f.HAYsTATEcNG);
      f.HAYsTATEcNG=0;
    }
  } 
}