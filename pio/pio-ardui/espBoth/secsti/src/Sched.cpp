#include "Sched.h"
#include <ArduinoJson.h>
#include <TimeLib.h>
#include "CONFIG.h"
// #include "Reqs.h"

// extern Reqs req;
extern char ipayload[250];

void Sched::actTime(){
  //Serial.println(unix);
  Serial.println(LLLL);
  //Serial.println(zone);
  time_t datetime = unix + zone*60*60;
  //Serial.println(datetime); 
  setTime(datetime);
  setSyncInterval(4000000); 
  Serial.print(hour()); 
  Serial.print(":");  
  Serial.println(minute());
}

bool Sched::deseriTime(){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(ipayload);
  root.prettyPrintTo(Serial);
  unix = root["unix"];
  LLLL = root["LLLL"];
  zone = root["zone"];
  return root.success();
  //actTime();
}

void Sched::adjRelay(int sr, cs_t& te){
  int bit =pow(2,sr);
  int mask = 31-bit; 
  bool relayState = te.onoff;
  if (te.reading >= te.hilimit){
    relayState=0;
  } else if (te.reading <= te.lolimit){
    relayState=1;
  }
  if (relayState != te.onoff){
    te.onoff = relayState;
    te.rec=1;
    int relayon = f.ISrELAYoN;
    if(te.onoff){
      relayon = relayon | bit;
    }else{
      relayon = relayon & mask;
    }
    if(relayon!=f.ISrELAYoN){
      f.ISrELAYoN = relayon;
      // req.pubTimr();
    }
    for (int i=0;i<prgs.numprgs;i++){
      if(prgs.prg[i].sr==sr){
        digitalWrite(prgs.prg[i].port, relayState); 
      }
    }
  } 
}