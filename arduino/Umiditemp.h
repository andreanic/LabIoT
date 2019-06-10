#ifndef UMIDITEMP_H
#define UMIDITEMP_H
#include <dht11.h>
#include "Sensor.h"
class Umiditemp: public Sensor {
//controllare valori di soglia anche umidita
  private:
     dht11 dht;
  public:
    sensorName = "KY‐015"
    description="sensore della temperatura e umidita";
    um="gradi centigradi e %";
    typeValue="Float";
    digitOrAnal="Digital";
    url="";
};
#endif
