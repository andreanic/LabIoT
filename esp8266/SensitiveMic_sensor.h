#ifndef SENSITIVEMIC_H
#define SENSITIVEMIC_H
#include "Sensor.h"

//NB per output digitale
class SensitiveMic_sensor: public Sensor {
  public:
    SensitiveMic_sensor(int pin,float soglia);
    SensitiveMic_sensor(int pin,float soglia,unsigned long frequenzacampionamento);
    ~SensitiveMic_sensor();
    float campiona();
};

SensitiveMic_sensor::SensitiveMic_sensor(int pin,float soglia): Sensor(pin,soglia) {}
SensitiveMic_sensor::SensitiveMic_sensor(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento) {}

SensitiveMic_sensor::~SensitiveMic_sensor(){}

float SensitiveMic_sensor::campiona() {
  /*this->value = static_cast<float>(random(this->soglia * 2));
  setSoglieSuccessive(this->soglia,this->value);
  return this->value;*/
  
  this->value = 1-static_cast<float>(digitalRead(this->pin));
  setSoglieSuccessive(this->value,this->soglia);
  return this->value;
} 
#endif
