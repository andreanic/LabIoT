#ifndef FUOCO_H
#define FUOCO_H
#include "Sensor.h"
class Fuoco: public Sensor {
  public:
    Fuoco();
    Fuoco(int pin,float soglia);
    Fuoco(int pin,float soglia,unsigned long frequenzacampionamento);
    ~Fuoco();
    float campiona();
    sensorName="KY‐026";
    description="sensore antincendio";
    uom="";
    typeValue="Float";
    digitOrAnal="Digitale";
    url="";
};

Fuoco::Fuoco(int pin,float soglia): Sensor(pin,soglia){
  this->sensorName = "Fuoco";
}
Fuoco::Fuoco(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento){
  this->sensorName = "Fuoco";
}

Fuoco::~Fuoco(){}

float Fuoco::campiona() { 
  int sensor = digitalRead(this->pin);
  this->value = static_cast<float>(sensor);
  setSoglieSuccessive(this->value,this->soglia);
  return this->value;
}
#endif
