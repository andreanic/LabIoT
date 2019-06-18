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
};

Fuoco::Fuoco(int pin,float soglia): Sensor(pin,soglia){
  this->sensorId="KY026";
  this->sensorName="sensore antincendio";
  this->description="sensore per il rilevamento di un incendio";
  this->uom="";
  this->typeValue="Float";
  this->isDigital=true;
  this->url="https://tkkrlab.nl/wiki/Arduino_KY-026_Flame_sensor_module";
}
Fuoco::Fuoco(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento){
  this->sensorId="KY026";
  this->sensorName="sensore antincendio";
  this->description="sensore per il rilevamento di un incendio";
  this->uom="";
  this->typeValue="Float";
  this->isDigital=true;
  this->url="https://tkkrlab.nl/wiki/Arduino_KY-026_Flame_sensor_module";
}

Fuoco::~Fuoco(){}

float Fuoco::campiona() { 
  int sensor = digitalRead(this->pin);
  this->value = static_cast<float>(sensor);
  setSoglieSuccessive(this->value,this->soglia);
  return this->value;
}
#endif
