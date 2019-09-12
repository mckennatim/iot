//{"id":4,"aid":5,"ev":3,"numdata":1,"pro":[[0,0,0],[15,26,1],[15,29,0]]}

#include <ArduinoJson.h>

#include "STATE.h"


prgs_t prgs {
    {0,255,1,2,{{0,0,76,73}}},
    {1,255,1,2,{{0,0,74,69}}},
    {2,255,1,1,{{0,0,0}}},
    {3,255,1,1,{{0,0,0}}},
    {4,255,1,1,{{0,0,0}}}
  };

void setup() {
  Serial.begin(115200);
  const char* kstr = "{\"id\":4,\"aid\":5,\"ev\":3,\"numdata\":1,\"pro\":[[0,0,0],[15,26,1],[15,29,0]]}";
  Serial.println(kstr);
  StaticJsonDocument<400> rot;
  deserializeJson(rot, kstr);
  int id = rot["id"];  
  Serial.print("id = ");
  Serial.println(id);
  JsonArray darr = rot["pro"];
  int prg[6][5];
  Serial.println(prgs.timr1.prg[0][2]);
  copyArray(darr, prgs.timr1.prg);
  Serial.println(prgs.timr1.prg[1][1]);
  Serial.println(darr.size());
  JsonArray a1 = darr[1];
  Serial.println(a1.size());
  int a = a1[1];
  Serial.println(a);
}

void loop() {

}