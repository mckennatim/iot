#include "CONFIG.h"

/*CONFIG extern const device variables*/
const sen_t SE {
  4,//number of different sensors
  6,//number of sensors
  {
    {1, {0}, "light", "BH1750"},//assumes SCL is D1(5) and SDA is D2(4)
    {2, {1,2}, "temp", "DS18B20a"},  
    // {2, {3,4}, "temp", "DS18B20b"},  
    {2, {3,4}, "temp-hum", "DHT11"},
    {1, {5}, "hygrometer", "ANALOG"},
    {1, {6}, "thermoco", "MAX31855"}//not used
  }
};
const portsin_t inpo {4, 5, 14, A0, 12, 15, 13};

/*CONFIG extern const universal variables*/
const labels_t la {
  {"devtime", "cmd", "prg", "req", "set", "progs"},
  6
};
flags_t f {0,0,5,28,0,0,31,0,0,0,{0,0,0,0,0}};
/*CONFIG extern structures (initial values, changeable)*/
srs_t srs {
  6,
  {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}}
};

char devid[9]=DEVID;
char owner[254]=OWNER;
char pwd[24]=PWD;
char mqtt_server[60]=MQTT_SERVER;
char mqtt_port[6]=MQTT_PORT;