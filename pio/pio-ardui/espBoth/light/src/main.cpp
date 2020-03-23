#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>
#include "CONST.h"


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

void doWhat(int sr){
  Serial.print(sr);
  Serial.println(F("dowhat baby assume it is a request for the reading"));
  //const char setyp= SRS.srlst[sr];
  Serial.println(SRS.srlst[sr]);
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
  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  //Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  //lightMeter.begin();
  //Serial.println(F("BH1750 light begin"));
  // Serial.println(SRS.se[0].id);
  // Serial.println(SRS.se[0].type);
  // Serial.println(SRS.se[0].model);
  // Serial.println(SRS.se[1].type);
  // Serial.println(SRS.se[1].model);
  // Serial.println(SRS.cs[0].prgo.prg[0][2]);
  // Serial.println(SRS.cs[0].prgo.prg[0][2]);
  // Serial.println(SRS.ti[0].prgo.aid);
  // Serial.println(SRS.ti[0].prgo.aid);

  Serial.println(COMP.owner);
  Serial.println(LA.scribedTo[0]);
  Serial.println(SA[1].model);

  doWhat(2);
  readSensors();

}


void loop() {
  readSensors();
  delay(1000);
}