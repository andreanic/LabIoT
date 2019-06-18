#ifndef VIBRATION_H
#define VIBRATION_H
#include "Sensor.h"
class Vibration_sensor: public Sensor {
  public:
    Vibration_sensor(int pin,float soglia);
    Vibration_sensor(int pin,float soglia,unsigned long frequenzacampionamento);
    ~Vibration_sensor();
    float campiona();
};

Vibration_sensor::Vibration_sensor(int pin,float soglia): Sensor(pin,soglia) {
  this->setMaxSoglie(40);
  this->sensorId="KY002";
  this->sensorName="vsensore ibrazione";
  this->description="sensore che rileva le vibrazioni";
  this->uom="";
  this->typeValue="Float";
  this->isDigital=true;
  this->url="https://tkkrlab.nl/wiki/Arduino_KY-002_Vibration_switch_module";
}
Vibration_sensor::Vibration_sensor(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento){
  this->setMaxSoglie(40);
  this->sensorId="KY002";
  this->sensorName="sensore vibrazione";
  this->description="sensore che rileva le vibrazioni";
  this->uom="";
  this->typeValue="Float";
  this->isDigital=true;
  this->url="https://tkkrlab.nl/wiki/Arduino_KY-002_Vibration_switch_module";
}

Vibration_sensor::~Vibration_sensor(){}

float Vibration_sensor::campiona() { 
 /* this->value = static_cast<float>(random(this->soglia * 2));
  setSoglieSuccessive(this->value,this->soglia);
  return this->value;
  */
	this->value = static_cast<float>(digitalRead(this->pin));
	setSoglieSuccessive(this->value,this->soglia);
	return this->value;
} 
#endif
