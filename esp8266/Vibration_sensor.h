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
 setMaxSoglie(40);
}
Vibration_sensor::Vibration_sensor(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento){
  setMaxSoglie(40);
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
