#include <Arduino.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include <PubSubClient.h>
#include "CONFIG.h"
#include "ConnWIFI.h"
#include "MQclient.h"//globals(extern) NEW_MAIL, itopic, ipayload + Console
#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include "Reqs.h"
#include "Sched.h"

Adafruit_MAX31855 tc(inpo.SPIcs);

ESP8266WebServer server;
BH1750 lightMeter;

OneWire oneWirea(inpo.DS18B20a);
DallasTemperature DS18B20a(&oneWirea);

OneWire oneWireb(inpo.DS18B20b);
DallasTemperature DS18B20b(&oneWireb);

DHT dht(inpo.Dht11, DHT11);

WiFiClient espClient;
PubSubClient client(espClient);
Console console(devid, client);
Reqs req(devid, client);
MQclient mq(devid, owner, pwd);
Sched sched;


void initShit(){
  pinMode(inpo.Dht11, INPUT);
  for (int i=0;i<SE.len;i++){
    Serial.println(SE.se[i].model);
    if(strcmp(SE.se[i].model, "BH1750")==0){
      Wire.begin();
      lightMeter.begin();
      Serial.println(F("BH1750 light begin"));
    }
    if(strcmp(SE.se[i].model, "DHT11")==0){
      dht.begin();
      Serial.println(F("DHT11 temp/hum begin"));
    }    
    if(strcmp(SE.se[i].model, "MAX31855")==0){
      tc.begin();
      Serial.println(F("MAX31855 thermoco begin"));
    }    
  }  
}

void updAndNotify(int i, int sr, int val){
  Serial.println(SE.se[i].model);
  srs.se[sr].reading=val;
  int bit =pow(2,sr);
  f.HAYsTATEcNG=f.HAYsTATEcNG | bit;  
}

void readSensors(){
  int senvals[SE.numsens];
  for(int i=0;i<SE.len;i++){
    if(strcmp(SE.se[i].model, "DS18B20a")==0){
      for(int j=0;j<SE.se[i].nums;j++) {
        DS18B20a.requestTemperatures(); 
        int sr = SE.se[i].ids[j];
        senvals[sr] = (int)DS18B20a.getTempFByIndex(j);
        if(abs(senvals[sr]-srs.se[sr].reading)>1 && senvals[sr] <120 && senvals[sr]>-20){
          updAndNotify(i,sr, senvals[sr]);
          printf("Temp%d: %d degrees \n",sr, senvals[sr]);
        }
      }
    }else if(strcmp(SE.se[i].model, "DS18B20b")==0){
      for(int j=0;j<SE.se[i].nums;j++) {
        int sr = SE.se[i].ids[j];
        DS18B20b.requestTemperatures(); 
        senvals[sr] = (int)DS18B20b.getTempFByIndex(j);
        if(abs(senvals[sr]-srs.se[sr].reading)>1 && senvals[sr] <120 && senvals[sr]>-20){
          updAndNotify(i,sr, senvals[sr]);
          printf("Temp%d: %d degrees \n",sr, senvals[sr]);
        }
      }
    }else if(strcmp(SE.se[i].model, "BH1750")==0){
      int lux = (int)lightMeter.readLightLevel();
      int sr = SE.se[i].ids[0];
      senvals[sr] = lux;
      if(abs(senvals[sr]-srs.se[sr].reading)>5 && senvals[sr] <1500 && senvals[sr]>0){
        updAndNotify(i,sr, senvals[sr]);
        printf("Light Level%d: %d lux \n",sr, senvals[sr]);
      }
    }else if(strcmp(SE.se[i].model, "DHT22")==0){
      int srt = SE.se[i].ids[0];
      int srh = SE.se[i].ids[1];      
      senvals[srt] = (int)(dht.readTemperature(true));
      senvals[srh] = (int)dht.readHumidity();
      if(abs(senvals[srt]-srs.se[srt].reading)>1 && senvals[srt] <100 && senvals[srt]>-20){
        updAndNotify(i,srt, senvals[srt]);
        printf("Temp%d: %d degrees, port: %d \n",srt, senvals[srt], inpo.Dht11);
      }
      if(abs(senvals[srh]-srs.se[srh].reading)>1 && senvals[srh] <100 && senvals[srh]>0){        
        updAndNotify(i,srh, senvals[srh]);
        printf("Humidity%d: %d percent \n",srh, senvals[srh]);
      }
    }else if(strcmp(SE.se[i].model, "DHT11")==0){
      int srt = SE.se[i].ids[0];
      int srh = SE.se[i].ids[1];      
      senvals[srt] = (int)dht.readTemperature(true);
      senvals[srh] = (int)dht.readHumidity();
      if(abs(senvals[srt]-srs.se[srt].reading)>1 && senvals[srt] <100 && senvals[srt]>-20){
        updAndNotify(i,srt, senvals[srt]);
        printf("Temp%d: %d degrees, port: %d \n",srt, senvals[srt], inpo.Dht11);
      }
      if(abs(senvals[srh]-srs.se[srh].reading)>1 && senvals[srh] <100 && senvals[srh]>0){        
        updAndNotify(i,srh, senvals[srh]);
        printf("Humidity%d: %d percent \n",srh, senvals[srh]);
      }
    }else if(strcmp(SE.se[i].model, "ANALOG")==0){
      int sr = SE.se[i].ids[0];
      senvals[sr] = map(constrain(analogRead(inpo.ANNALOG),460,1023),463,1023,100,0);
      if(abs(senvals[sr]-srs.se[sr].reading)>1 && senvals[sr] <100 && senvals[sr]>0){
        updAndNotify(i,sr, senvals[sr]);
        printf("Soil Moisture%d: %d percent \n",sr, senvals[sr]);
      }
    }else if(strcmp(SE.se[i].model, "MAX31855")==0){
      int sr = SE.se[i].ids[0];
      double ftemp =tc.readInternal();
      Serial.println(ftemp);
      senvals[sr] = (int)ftemp;
      if(abs(senvals[sr]-srs.se[sr].reading)>1 && senvals[sr] <550 && senvals[sr]>0){
        updAndNotify(i,sr, senvals[sr]);
        printf("Thermocpouple%d: %d degreesF \n",sr, senvals[sr]);
      }
    }
  }
}

void setup(){
  Serial.begin(115200);
  EEPROM.begin(512);
  initShit();
  getOnline();//config.cpp
  Serial.println(la.scribedTo[0]);
  client.setServer(mqtt_server, atoi(mqtt_port));
  client.setCallback(handleCallback); //in Req.cpp
}

time_t before = 0;
time_t schedcrement = 0;
time_t inow;

void loop() {
  if(NEW_MAIL){
    Serial.println("hay NEW_MAIL");
    req.processInc();
    NEW_MAIL=0;
  } 
  if(!client.connected()){
    Serial.println(owner);
     mq.reconn(client);
  }else{
    client.loop();
  }  
  inow = millis();
  if (inow - before > 1000) {
    before = inow;
    readSensors();
    if(f.HAYsTATEcNG>0){
      req.pubState(f.HAYsTATEcNG);
      f.HAYsTATEcNG=0;
    }
  } 
}