#ifndef CONST_h
#define CONST_h

  #include <TimeLib.h>
  #include <TimeAlarms.h>
  #include <ESP8266WebServer.h>
	
  #define sizeOf(a) (sizeof(a) / sizeof(a[0]))

  struct prg_t{
    int id;
    AlarmID_t aid;
    int ev;
    int prg[11][5];//max 11 events [hr,min,max,min]  
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
  static sen_t SE {
    4,//number of different sensors
    7,//number of sensors
    {{1, {0}, "light", "BH1750"},//assumes 
    {2, {1,2}, "temp", "DS18B20a"},  
    {2, {3,4}, "temp", "DS18B20b"},  
    {2, {5,6}, "temp-hum", "DHT22"}}
  };

  struct portsin_t{
    int DS18B20a;
    int DS18B20b;
    int DHT22a;
  };
  static portsin_t inpo {4, 5, 14};


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

  // struct server_t{
  //   char owner[254];
  //   char pwd[24];
  //   char mqtt_server[60];
  //   char mqtt_port[6];
  // };  

  // server_t COMP = {
  //   "tim@sitebuilt.net",
  //   "geniot",
  //   "sitebuilt.net",
  //   "1884"
  // };

  struct labels_t {
    char scribedTo[6][8]; 
    int numcmds;
  };

  static labels_t LA {
    {"devtime", "cmd", "prg", "req", "set", "progs"},
    6
  };

  // #define OWNER "tim@sitebuilt.net"
  // #define PWD "geniot"
  // #define MQTT_SERVER "sitebuilt.net"
  // #define MQTT_PORT "1884"

  // extern char* OWNER ="tim@sitebuilt.net";
  // extern const char* PWD ="geniot";
  // extern const char* MQTT_SERVER= "sitebuilt.net";
  // extern const char* MQTT_PORT= "1884";

  // extern char owner[254] ="tim@sitebuilt.net";
  // extern char pwd[24] ="geniot";
  // extern char mqtt_server[60]= "sitebuilt.net";
  // extern char mqtt_port[6]= "1884";


#endif

