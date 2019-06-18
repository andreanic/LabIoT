#ifndef SUONO_H
#define SUONO_H
#include "Sensor.h"
class Suono: public Sensor {
  public:
    Suono(int pin,float soglia);
    Suono(int pin,float soglia,long frequenzacampionamento);
    ~Suono();
    float campiona();
};

Suono::Suono(int pin,float soglia): Sensor(pin,soglia){
  this->sensorId="GROVE SOUND SENSOR";
  this->sensorName = "sensore microfonico";
  this->description="microfono per misurare il suono nell\'ambiente";
  this->uom="decibel";
  this->typeValue="Float";
  this->isDigital=false;
  this->url="http://wiki.seeedstudio.com/Grove-Sound_Sensor/";
}
Suono::Suono(int pin,float soglia,long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento){
  this->sensorId="GROVE SOUND SENSOR";
  this->sensorName = "sensore microfonico";
  this->description="microfono per misurare il suono nell\'ambiente";
  this->uom="decibel";
  this->typeValue="Float";
  this->isDigital=false;
  this->url="http://wiki.seeedstudio.com/Grove-Sound_Sensor/";
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
