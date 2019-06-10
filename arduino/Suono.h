#ifndef SUONO_H
#define SUONO_H
#include "Sensor.h"
class Suono: public Sensor {
  public:
    Suono(int pin,float soglia);
    Suono(int pin,float soglia,long frequenzacampionamento);
    ~Suono();
    float campiona();
    sensorName = "GROVE - SOUND SENSOR"
    description="microfono";
    uom="decibel";
    typeValue="Float";
    digitOrAnal="Analogico";
    url="";
};

Suono::Suono(int pin,float soglia): Sensor(pin,soglia){
  this->sensorName = "Suono";  
}
Suono::Suono(int pin,float soglia,long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento){
  this->sensorName = "Suono";  
}

Suono::~Suono(){}

float Suono::campiona() {
  int sum=0;
  for(int i=0; i<32; i++){
    sum += analogRead(this->pin);
  }
  sum >>= 5;
  this->value = static_cast<float>(sum);
  setSoglieSuccessive(this->value,this->soglia);
  return this->value;
}
#endif
