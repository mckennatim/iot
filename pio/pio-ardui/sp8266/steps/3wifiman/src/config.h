#ifndef config_h
#define config_h

extern char devid[9];
extern char owner[254];
extern char pwd[24];
extern char mqtt_server[60];
extern char mqtt_port[6];
extern char sensor_type[24];

void getOnline();
void saveConfig();
void reconfig(char pload[]);

#endif