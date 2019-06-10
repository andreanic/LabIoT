#ifndef TILT_H
#define TILT_H
#include "Sensor.h"
class Tilt_sensor: public Sensor {
  public:
    Tilt_sensor(int pin,float soglia);
    Tilt_sensor(int pin,float soglia,unsigned long frequenzacampionamento);
    ~Tilt_sensor();
    float campiona();
};

Tilt_sensor::Tilt_sensor(int pin,float soglia): Sensor(pin,soglia) {
  setMaxSoglie(40); 
  sensorName="Tilt";
  description="sensore tilt";
  um = "";
  typeValue="string";
  digitOrAnal="float";
  url="";
}
Tilt_sensor::Tilt_sensor(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento) {
  setMaxSoglie(40);
  description="sensore tilt";
  um = "";
  typeValue="int";
  digitOrAnal="digital";
  url="";  
}

Tilt_sensor::~Tilt_sensor(){}

float Tilt_sensor::campiona() {
	this->value = static_cast<float>(digitalRead(this->pin));
	setSoglieSuccessive(this->value,this->soglia);
	return this->value;
} 
#endif
