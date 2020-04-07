#include "CONFIG.h"

/*timers test program*/

char devid[9]="CYURD112";
char owner[254]="tim@sitebuilt.net";
char pwd[24]="geniot";
char mqtt_server[60]="sitebuilt.net";
char mqtt_port[6]="1884";

/*CONFIG extern const device variables*/
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
const portsin_t inpo {D2, D1, D5, A0, D6, D8, D7};//shares i2c D2 and D1

const srpos_t outpos {
  3, //numpos
  {{2,D0}, {7,D3}, {8,D4}} //pod.sr,pod.portnum
};

/*CONFIG extern const universal variables*/
const labels_t la {
  {"devtime", "cmd", "prg", "req", "set", "progs"},
  6
};
flags_t f {0,0,5,28,0,0,31,0,0,0,{0,0,0,0,0}};
/*CONFIG extern structures (initial values, changeable)*/

srs_t srs {
  5,
  {{0,45,0},{1,46,0},{3,47,0},{4,48,0},{5,49,0}},
  1,
  {{2,44,0,68,64,0}},
  2,
  {{7,0,0},{8,0,0}}
};



