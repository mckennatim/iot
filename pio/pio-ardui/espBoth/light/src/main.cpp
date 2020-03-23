#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include "CONST.h"
#include "config.h"


ESP8266WebServer server;
BH1750 lightMeter;

OneWire oneWirea(inpo.DS18B20a);
DallasTemperature DS18B20a(&oneWirea);

OneWire oneWireb(inpo.DS18B20b);
DallasTemperature DS18B20b(&oneWireb);

#define DHTTYPE DHT22 
#define DHTPIN inpo.DHT22a
DHT dht22(DHTPIN, DHTTYPE);



void initShit(){
  for (int i=0;i<SE.len;i++){
    Serial.println(SE.se[i].model);
    if(strcmp(SE.se[i].model, "BH1750")==0){
      Wire.begin();
      lightMeter.begin();
      Serial.println(F("BH1750 light begin"));
    }
  }  
}

void readSensors(){
  int senvals[SE.numsens];
  for(int i=0;i<SE.len;i++){
    Serial.println(SE.se[i].model);
    if(strcmp(SE.se[i].model, "DS18B20a")==0){
      for(int j=0;j<SE.se[i].nums;j++) {
        DS18B20a.requestTemperatures(); 
        int sr = SE.se[i].ids[j];
        senvals[sr] = (int)DS18B20a.getTempFByIndex(j);
        printf("Temp%d: %d degrees \n",sr, senvals[sr]);
      }
    }else if(strcmp(SE.se[i].model, "DS18B20b")==0){
      for(int j=0;j<SE.se[i].nums;j++) {
        int sr = SE.se[i].ids[j];
        DS18B20b.requestTemperatures(); 
        senvals[sr] = (int)DS18B20a.getTempFByIndex(j);
        printf("Temp%d: %d degrees \n",sr, senvals[sr]);
      }
    }else if(strcmp(SE.se[i].model, "BH1750")==0){
      int lux = (int)lightMeter.readLightLevel();
      int sr = SE.se[i].ids[0];
      senvals[sr] = lux;
      printf("Light%d: %d lux \n",sr, senvals[sr]);
    }else if(strcmp(SE.se[i].model, "DHT22")==0){
      int srt = SE.se[i].ids[0];
      int srh = SE.se[i].ids[1];      
      senvals[srt] = (int)(dht22.readTemperature(true));
      senvals[srh] = (int)dht22.readHumidity();
      printf("Temp%d: %d degrees \n",srt, senvals[srt]);
      printf("Humidity%d: %d percent \n",srh, senvals[srh]);
    }
  }
}

void setup(){
  Serial.begin(115200);
  initShit();
  getOnline();//config.cpp
  Serial.println(LA.scribedTo[0]);
  // printf("%s \n", OWNER);
}


void loop() {
  readSensors();
  delay(1000);
}