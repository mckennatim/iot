#ifndef CONFIG_h
#define CONFIG_h

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
    int ids[6]; //sr id
    char type[12];
    char model[12];
  };

  struct sen_t {
    int len;
    int numsens;
    senso_t se[5];
  };
  extern const sen_t SE;

  extern int states[7][1];
  // int state[7][1];

  struct astate_t{
    int id;
    int stsz;
    int stdata[3];
    bool state; 
    bool rec;
  };



  struct portsin_t{
    int DS18B20a;
    int DS18B20b;
    int Dht11;
    int ANNALOG;
    int SPIdo;
    int SPIcs;//d8
    int SPIcl;
  };
  extern const portsin_t inpo; 

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

  struct labels_t {
    char scribedTo[6][8]; 
    int numcmds;
  };

  extern const labels_t la ;

  extern char devid[9];
	extern char owner[254];
	extern char pwd[24];
	extern char mqtt_server[60];
	extern char mqtt_port[6];
	extern char sensor_type[24];
//static const uint8_t SDA = 4;
//static const uint8_t SCL = 5;
//
//static const uint8_t LED_BUILTIN = 2;
//static const uint8_t BUILTIN_LED = 2;
//
//static const uint8_t D0 = 16;
//static const uint8_t D1 = 5;
//static const uint8_t D2 = 4;
//static const uint8_t D3 = 0;
//static const uint8_t D4 = 2;
//static const uint8_t D5 = 14;
//static const uint8_t D6 = 12;
//static const uint8_t D7 = 13;
//static const uint8_t D8 = 15;
//static const uint8_t RX = 3;
//static const uint8_t TX = 1;
#endif

