#include "CONFIG.h"

/*dev extern device variables*/
char devid[9]="CYURD112";
char owner[254]="tim@sitebuilt.net";
char pwd[24]="geniot";
char mqtt_server[60]="sitebuilt.net";
char mqtt_port[6]="1884";
/*dev*/

/*CONFIG extern const device variables*/
/*INCOMING const mqtt topics*/
const topics_t TPC {
  5,
  {"devtime", "cmd", "prg", "req", "set"}
};
/*PORTS for INPUT*/
const portsin_t inpo {D2, D1, D5, A0, D6, D8, D7};//shares i2c D2 and D1
/*SE constant declarations*/  
const sen_t SE {
  4,//number of different sensor types
  6,//number of sensors(numsens)
  {
    {1, {0}, "light", "BH1750"},//assumes SCL is D1(5) and SDA is D2(4)
    {2, {1,2}, "temp", "DS18B20a"},  
    // {2, {3,4}, "temp", "DS18B20b"},  
    {2, {3,4}, "temp-hum", "DHT11"},
    {1, {5}, "hygrometer", "ANALOG"}
    //{1, {6}, "thermoco", "MAX31855"}//not used
  }
};
/*------------------------------------------------------
CONFIG extern structures (initial values, changeable)*/
/*srs extern data structure initalization
state of relays and sensors */ 
srs_t srs {
  5,
  {{0,45,1,0},{1,46,1,0},{3,47,0,0},{4,48,0,0},{5,49,0,0}},
  1,
  {{2,44,0,68,64,1,0}},
  2,
  {{6,0,1,0},{7,0,0,0}}
};
/*prgs extern data structure initalization*/ 
prgs_t prgs{
  3,
  {
    {2,255,1,2,{{0,0,69,67}},D0}, 
    {6,255,1,1,{{0,0,1}},D3},
    {7,255,1,1,{{0,0,0}},D4}
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
  0,//HAYsTATEcNG
  0,//CKaLARM
  0,//ISrELAYoN
  {0,0,0,0,0,0,0,0,0,0}//tIMElEFT[10]
};

// const srpos_t outpos {
//   3, //numpos
//   {{2,D0}, {7,D3}, {8,D4}} //pod.sr,pod.portnum
// };
