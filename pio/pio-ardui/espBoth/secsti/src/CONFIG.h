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

  /*SE constant declarations*/  
  struct senso_t{
    int nums;
    int ids[6]; //srs/portin
    char type[12];
    char model[12];
  };
  struct sen_t {
    int numtypes;
    int numsens;
    senso_t stype[6];
  };
  extern const sen_t SE;
  /*SE constant declarations*/ 

  /*srs data structure declarations*/ 
  struct se_t {//sensors
    int sr;
    int reading;
    int rec;
  };
  struct cs_t {//controlled sensors
    int sr;
    int reading;
    int onoff;
    int hilimit;
    int lolimit;
    int rec;   
  };
  struct ti_t {//timers
    int sr;
    int onoff;
    int rec;   
  };
  struct srs_t {
    int numse;
    se_t se[5];
    int numcs;
    cs_t cs[1];
    int numti;
    ti_t ti[2];
  };
  extern srs_t srs;
   /*srs data structure declarations*/  

  struct astate_t{
    int id;
    int stsz;
    int stdata[3];
    bool state; 
    bool rec;
  };

  struct portsin_t{
    uint8_t DS18B20a;
    uint8_t DS18B20b;
    uint8_t Dht11;
    uint8_t ANNALOG;
    uint8_t SPIdo;
    uint8_t SPIcs;//d8
    uint8_t SPIcl;
  };
  extern const portsin_t inpo; 

  /*OUTPUT ports*/
  struct srpo_t{
    int sr;
    uint8_t portnum;
  };

  struct srpos_t {
    int numpos;
    srpo_t pod[3];
  };

  extern const srpos_t outpos;
  /*OUTPUT ports*/

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

  struct flags_t{
  bool aUTOMA;
  bool fORCErESET;  
  int cREMENT;
  int HAStIMR; //11100(28) 4,8, and 16 have timers not temp
  int IStIMERoN;//11100 assume some time left, timers with tleft>0 
  int HAYpROG;// = senrels with events>1
  int HAYpROGcNG;// 11111(31 force report) some prog change int or ext
  int HAYsTATEcNG; //11111(31 force report) some state change int or ext
  int CKaLARM; //11111 assume alarm is set at start
  int ISrELAYoN;// = summary of relay states  
  int tIMElEFT[5];// =[0,0,56,0,0] timeleft in timrs
};

extern flags_t f;

// static const uint8_t SDA = 4;
// static const uint8_t SCL = 5;

// static const uint8_t LED_BUILTIN = 2;
// static const uint8_t BUILTIN_LED = 2;

// static const uint8_t D0 = 16;
// static const uint8_t D1 = 5;
// static const uint8_t D2 = 4;
// static const uint8_t D3 = 0;
// static const uint8_t D4 = 2;
// static const uint8_t D5 = 14;
// static const uint8_t D6 = 12;
// static const uint8_t D7 = 13;
// static const uint8_t D8 = 15;
// static const uint8_t RX = 3;
// static const uint8_t TX = 1;
#endif

