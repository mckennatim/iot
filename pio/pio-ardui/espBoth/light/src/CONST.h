#ifndef CONST_h
#define CONST_h

  #include <TimeLib.h>
  #include <TimeAlarms.h>
  #include <ESP8266WebServer.h>
	
  #define sizeOf(a) (sizeof(a) / sizeof(a[0]))
  
  // extern ESP8266WebServer server;
  // extern BH1750 lightMeter;

  // extern OneWire oneWire(4);
  // extern DallasTemperature DS18B20(&oneWire);

  struct prg_t{
    int id;
    AlarmID_t aid;
    int ev;
    int prg[11][5];//max 11 events [hr,min,max,min]  
  };

  struct sensor_t{
    int id;
    char type[12];
    char model[12];
    int inport;
  };

  struct senso_t{
    int nums;
    int ids[6];
    char type[12];
    char model[12];
  };

  struct sen_t {
    int len;
    int numsens;
    senso_t se[4];
  };

  struct portsin_t{
    int DS18B20a;
    int DS18B20b;
    int DHT22a;
  };

  portsin_t inpo {4, 5, 14};

  sen_t SE {
    4,//number of different sensors
    7,//number of sensors
    {{1, {0}, "light", "BH1750"},
    {2, {1,2}, "temp", "DS18B20a"},  
    {2, {3,4}, "temp", "DS18B20b"},  
    {2, {5,6}, "temp-hum", "DHT22"}}
  };

  sensor_t SA[3] ={
    {0, "light", "BH1750", 4},
    {1, "temp", "DS18B20", 5},  
    {2, "temp", "DS18B20", 5}
  };

  struct ctrld_sensor_t{
    int id;
    char type[12];
    char model[12];
    int inport;
    int outport;
    prg_t prgo;
  };

  struct timr_t{
    int id;
    char type[12];
    int outport;
    prg_t prgo;  
  };

  struct sr_t{
    int numsrs[3];
    char srlst[4][3];
    sensor_t se[2];
    ctrld_sensor_t cs[1];
    timr_t ti[1];
  };

  sr_t SRS {
    {2, 1, 1},
    {"se", "se", "cs", "ti"},
    {
      {0, "light", "BH1750", 4},
      {1, "temp", "DS18B20", 5}
    },
    {
      {2, "temp", "DS18B20", 5, 12, 
        {2, 255, 1, {{0,0,65,63}}}
      }
    },
    {
      {3, "timer", 13,
        {3, 255, 1, {{0,0,1}}}
      }
    }
  };

  struct server_t{
    char owner[254] ;
    char pwd[24];
    char mqtt_server[60];
    char mqtt_port[6];
  };  

  server_t COMP = {
    "tim@sitebuilt.net",
    "geniot",
    "sitebuilt.net",
    "1884"
  };

  struct labels_t {
    char scribedTo[6][8]; 
    int numcmds;
  };

  labels_t LA {
    {"devtime", "cmd", "prg", "req", "set", "progs"},
    6
  };



#endif

