#include "Reqs.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <TimeLib.h>
#include "ConnWIFI.h" //getOnline() readConfig()devid owner pwd
#include "Sched.h"

extern Sched sched;
extern char itopic[40];
extern char ipayload[250];

Reqs::Reqs(char* devid, PubSubClient& client ){
  cdevid = devid;
  cclient = client;
}

//{"devtime", "cmd", "prg", "req", "set", "progs"}
void Reqs::processInc(){
  for (int i=0;i<la.numcmds;i++){
    if(strcmp(la.scribedTo[i], itopic)==0){
    	switch (i){
        case 0:
          Serial.println("case 0 is what devtime?");
          sched.deseriTime();
          sched.actTime();
          break;
        default: 
        	Serial.print(i);         
          Serial.println(": in processInc default");
          break;           
      }
    }
  }
}   

void Reqs::pubState(int hc){
  Serial.print("in publishState w: ");
  Serial.println(hc);
  char srstate[20];
  strcpy(srstate,cdevid);
  strcat(srstate,"/srstate");  
  char astr[120];
  for( int i=1; i<=SE.numsens, i++){
    if(hc&i==i){
      Serial.println("publish state for ");
    }
  }
}