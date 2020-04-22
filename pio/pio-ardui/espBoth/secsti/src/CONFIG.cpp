#include "CONFIG.h"
// #include <Arduino.h>//if CUSTOM CODE

/*DESCRIPTION
Cascada 
Pond D5 OUT when on acivates lohi water circuit+relay
  and pond pumps relay (120V)
Garden D6 & D7 OUT irrigation activate (24V)
Transformer D8 activated when either D5,D6 or D7 hi
hay NO sensors connected to esp8266
CONFIG_CYURD116cascada running on espboth/secsti
has CUSTOM CODE
*/

/*CUSTOM CODE
Transformer D8 activated when either D5,D6 or D7 hi
srs.ti[0] (sr 0) onoff for D5
srs.ti[1] (sr 1) onoff for D6
srs.ti[2] (sr 2) onoff for D7
(see srs.ti_t and prgs.prg_t)
otherwise make some DUMMY custom function
void customInit(){
  if(0==1){
    int dog =3;
  }
};
void customLoop() {
  if(0==1){
    int dog =3;
  }
};
*/ 
void customInit(){
  pinMode(D8, OUTPUT);
  digitalWrite(D8, HIGH);
}
void customLoop(){
  int bef = digitalRead(D8);
  if(srs.ti[0].onoff==1 || srs.ti[1].onoff==1 || srs.ti[2].onoff==1){
    digitalWrite(D8, HIGH);
  }else{
    digitalWrite(D8, LOW);
  }
  int aft = digitalRead(D8);
  if(aft != bef){
    Serial.print("D8 is ");
    Serial.println(aft);
  }
}

/*SERVER
dev extern device variables*/
char devid[9]="CYURD116";
char owner[254]="tim@sitebuilt.net";
char pwd[24]="geniot";
char mqtt_server[60]="sitebuilt.net";
char mqtt_port[6]="1884";
/*dev*/

/*SPECS
CONFIG extern const device variables
INCOMING const mqtt topics*/
const topics_t TPC {
  5,
  {"devtime", "cmd", "prg", "req", "set"}
};
/*PORTS for INPUT*/
const portsin_t inpo {
  0, //DS18b20a
  0, //DS18b20b
  0,//dht11
  0, //ANALOG
  0, //SPIdo
  0, //SPIcs
  0};//shares i2c D2 and D1
/*SE constant declarations*/  
const sen_t SE {
  0,//number of different sensor types
  0,//number of sensors(numsens)
  {}
};
/*------------------------------------------------------
CONFIG extern structures (initial values, changeable)*/
/*srs extern data structure initalization
state of relays and sensors */ 
srs_t srs {
  3,//numsr
  0,//sumse
  {},
  0,//numcs
  {},
  3,//numti
  { //{sr,onoff,rec,isnew}
    {0,0,1,0},{1,0,1,0},{2,0,1,0}
  }
};
/*prgs extern data structure initalization*/ 
prgs_t prgs{
  3,//numprgs
  { //sr,aid,ev,numdata,prg[[]],port,hms
    {0,255,1,2,{{0,0,0}},D5,1506}, 
    {1,255,1,1,{{0,0,0}},D6,1504},
    {2,255,1,1,{{0,0,0}},D7,1503}
  }
};
/*flags extern data structure*/
flags_t f {
  0,//aUTOMA
  0,//fORCErESET
  5,//cREMENT
  96,//HAStIMR 1100000 64+32=96
  0,//IStIMERoN
  198,//HAYpROG 11000010 =128+64+4=198
  1023,//HAYsTATEcNG
  0,//CKaLARM
  0,//ISrELAYoN
  {0,0,0,0,0,0,0,0,0,0}//tIMElEFT[10]
};

// nxtalarr_t nxtal {
//   0,//num
//   {//sr,aid,hms (h*60+m)*20+sr
//     {0,255,29000},
//     {1,255,29000},
//     {2,255,29000},
//     {3,255,29000},
//     {99,255,29001},
//     {99,255,29002},
//     {99,255,29006},
//     {99,255,29004},
//     {99,255,29000},
//     {99,255,29000}
//   }
// };
    

// const srpos_t outpos {
//   3, //numpos
//   {{2,D0}, {7,D3}, {8,D4}} //pod.sr,pod.portnum
// };
