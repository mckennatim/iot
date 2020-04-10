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
BH1750 lightMeter; //i2c auto uses SDA(D2) and SCL(D1)

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
  for (int i=0;i<SE.numtypes;i++){
    Serial.println(SE.stype[i].model);
    if(strcmp(SE.stype[i].model, "BH1750")==0){
      Wire.begin();
      lightMeter.begin();
      Serial.println(F("BH1750 light begin"));
    }
    if(strcmp(SE.stype[i].model, "DHT11")==0){
      dht.begin();
      Serial.println(F("DHT11 temp/hum begin"));
    }    
    if(strcmp(SE.stype[i].model, "MAX31855")==0){
      tc.begin();
      Serial.println(F("MAX31855 thermoco begin"));
    }    
  }  
}

void setSrs(int srid, int reading){
  for (int i=0; i<srs.numse;i++){
    if(srs.se[i].sr==srid){
      srs.se[i].reading=reading;
      srs.se[i].isnew=1;
    }
  }
  for (int j=0; j<srs.numcs;j++){
    if(srs.cs[j].sr==srid){
      srs.cs[j].reading=reading;
      srs.cs[j].isnew=1;
      sched.adjRelay(srid, srs.cs[j]);
    }
  } 
}

void setIfDif (int srid, int reading, int old, int dif, int hi, int lo){
  if(abs(reading-old)>dif && reading<hi && reading>lo){
    setSrs(srid, reading);
    int bit =pow(2,srid);
    f.HAYsTATEcNG=f.HAYsTATEcNG | bit; 
    printf("Sensor %d: reading: %d  \n",srid, reading);
  }
}

void readSensors(){
  int senvals[SE.numsens]; 
  int sr;
  int old;
  for(int i=0;i<SE.numtypes;i++){//check all the types incl.
    if(strcmp(SE.stype[i].model, "DS18B20a")==0){
      for(int j=0;j<SE.stype[i].nums;j++) {
        DS18B20a.requestTemperatures(); 
        sr = SE.stype[i].ids[j];
        old = req.getStoredReading(sr);
        senvals[sr] = (int)DS18B20a.getTempFByIndex(j);
        setIfDif (sr, senvals[sr] , old, 1, 120, -20);
      }
    }else if(strcmp(SE.stype[i].model, "DS18B20b")==0){
      for(int j=0;j<SE.stype[i].nums;j++) {
        sr = SE.stype[i].ids[j];
        DS18B20b.requestTemperatures(); 
        sr = SE.stype[i].ids[j];
        old = req.getStoredReading(sr);
        senvals[sr] = (int)DS18B20a.getTempFByIndex(j);
        setIfDif (sr, senvals[sr] , old, 1, 120, -20);
      }
    }else if(strcmp(SE.stype[i].model, "BH1750")==0){
      int lux = (int)lightMeter.readLightLevel();
      sr = SE.stype[i].ids[0];
      senvals[sr] = lux;
      sr = SE.stype[i].ids[0];
      old = req.getStoredReading(sr);
      setIfDif (sr, senvals[sr] , old, 5, 1500, 0);
    }else if(strcmp(SE.stype[i].model, "DHT22")==0){
      int srt = SE.stype[i].ids[0];
      int srh = SE.stype[i].ids[1];      
      senvals[srt] = (int)(dht.readTemperature(true));
      senvals[srh] = (int)dht.readHumidity();
      old = req.getStoredReading(srt);
      setIfDif (srt, senvals[srt] , old, 1, 120, -20);
      old = req.getStoredReading(srh);
      setIfDif (srh, senvals[srh] , old, 1, 100, 0);
    }else if(strcmp(SE.stype[i].model, "DHT11")==0){
      int srt = SE.stype[i].ids[0];
      int srh = SE.stype[i].ids[1];      
      senvals[srt] = (int)dht.readTemperature(true);
      senvals[srh] = (int)dht.readHumidity();
      old = req.getStoredReading(srt);
      setIfDif (srt, senvals[srt] , old, 2, 120, -20);
      // printf("DHTll temp sensro:%d, reading:%d \n", srt, senvals[srt]);
      old = req.getStoredReading(srh);
      setIfDif (srh, senvals[srh] , old, 3, 100, 0);
      // printf("DHTll humidity sensro:%d, reading:%d \n", srh, senvals[srh]);
    }else if(strcmp(SE.stype[i].model, "ANALOG")==0){
      sr = SE.stype[i].ids[0];
      senvals[sr] = map(constrain(analogRead(inpo.ANNALOG),460,1023),463,1023,100,0);
      old = req.getStoredReading(sr);
      setIfDif (sr, senvals[sr] , old, 1, 100, 0);
    }else if(strcmp(SE.stype[i].model, "MAX31855")==0){
      sr = SE.stype[i].ids[0];
      double ftemp =tc.readInternal();
      Serial.println(ftemp);
      senvals[sr] = (int)ftemp;
      old = req.getStoredReading(sr);
      setIfDif (sr, senvals[sr] , old, 1, 100, 0);
    }
  }
}

void setup(){
  Serial.begin(115200);
  EEPROM.begin(512);
  initShit();
  getOnline();//config.cpp
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