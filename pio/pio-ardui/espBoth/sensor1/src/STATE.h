#ifndef STATE_h
#define STATE_h
#include <TimeLib.h>
#include <TimeAlarms.h>

#define sizeOf(a) (sizeof(a) / sizeof(a[0]))

struct ports_t {
  int sensor; //io4d2; //ONE_WIRE_BUS temp sensor input
};

struct labels_t {
  static const char* scribedTo[]; 
  static const int numcmds;
};

struct sense_t {
	int sense;
	bool state;
  bool rec;
};


struct state_t{
	sense_t sense1;
};

struct flags_t{
  bool aUTOMA;
  bool fORCErESET;  
  int cREMENT;
  int HAYsTATEcNG; //11111(31 force report) some state change int or ext
};


#endif