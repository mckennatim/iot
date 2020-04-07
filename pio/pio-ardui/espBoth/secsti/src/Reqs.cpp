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

iscsidx_t Reqs::getTypeIdx(int srid){
  iscsidx_t ici;
  for (int i=0; i<srs.numse;i++){
    if(srs.se[i].sr==srid){
      ici.srtype=0;
      ici.idx=i;
    }
  }
  for (int j=0; j<srs.numcs;j++){
    if(srs.cs[j].sr==srid){
      ici.srtype=1;
      ici.idx=j;
    }
  }
  for (int k=0; k<srs.numti;k++){
    if(srs.ti[k].sr==srid){
      ici.srtype=2;
      ici.idx=k;
    }
  }
  return ici;
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
      iscsidx_t ici = getTypeIdx(i);
      if (ici.srtype==0){//se
        sprintf(astr, "{\"id\":%d, \"darr\":[%d], \"new\":%d}", srs.se[ici.idx].sr, srs.se[ici.idx].reading,  srs.se[ici.idx].rec);
        srs.se[ici.idx].rec=0;
      }else if (ici.srtype==1){//cs
        sprintf(astr, "{\"id\":%d, \"darr\":[%d, %d, %d, %d], \"new\":%d}", srs.cs[ici.idx].sr, srs.cs[ici.idx].reading, srs.cs[ici.idx].onoff, srs.cs[ici.idx].hilimit, srs.cs[ici.idx].lolimit, srs.cs[ici.idx].rec);  
        srs.cs[ici.idx].rec=0;    
      }else{//ti
        sprintf(astr, "{\"id\":%d, \"darr\":[%d], \"new\":%d}", srs.ti[ici.idx].sr, srs.ti[ici.idx].onoff,  srs.ti[ici.idx].rec);
        srs.ti[ici.idx].rec=0;
      }
      clpub(srstate, astr);
    }
  }
}

void Reqs::pubTimr(){
  char timr[20];
  strcpy(timr,cdevid);
  strcat(timr,"/timr"); 
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["cREMENT"]=f.cREMENT;
  root["IStIMERoN"]=f.IStIMERoN;//11100 assume some time left, timers with tleft>0 
  root["ISrELAYoN"]=f.ISrELAYoN;// = summary of relay states  
  JsonArray& tleft = root.createNestedArray("tIMElEFT");
  for(int i=0;i<5;i++){
    tleft.add(f.tIMElEFT[i]);
  }
  char ast[180];
  root.printTo(ast, sizeof(ast));
  clpub(timr,ast);  
}