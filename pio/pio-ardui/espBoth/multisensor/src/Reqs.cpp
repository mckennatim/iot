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

void Reqs::clpub(char status[20], char astr[200]){
  Serial.print("client connected: ");
  Serial.println(cclient.connected() ? "true" : "false");
  if (cclient.connected()){
    cclient.publish(status, astr, true);
  }   
  Serial.print(status);
  Serial.println(astr);
}

void Reqs::pubState(int hc){
  Serial.print("in publishState w: ");
  Serial.println(hc);
  char srstate[20];
  strcpy(srstate,cdevid);
  strcat(srstate,"/srstate");  
  char astr[200];
  for( int i=0; i<SE.numsens; i++){
    int bit =pow(2,i);
    if((hc&bit)==bit){
      Serial.println("publish state for ");
      sprintf(astr, "{\"id\":%d, \"darr\":[%d], \"new\":%d}", i, srs.se[i].reading, srs.se[i].rec);
      clpub(srstate, astr);
      srs.se[i].rec=0;
    }
  }
}