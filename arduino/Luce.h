#ifndef LUCE_H
#define LUCE_H
#include "Sensor.h"
class Luce: public Sensor {
  public:
    Luce(int pin,float soglia);
    Luce(int pin,float soglia,unsigned long frequenzacampionamento);
    ~Luce();
    float campiona();
    sensorName="GROVE - LIGHT SENSOR";
    description="sensore della luce";
    uom="";
    typeValue="Float";
    digitOrAnal="Analogico";
    url="";
};

Luce::Luce(int pin,float soglia): Sensor(pin,soglia) {
  this->sensorName = "Luce";
}
Luce::Luce(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento) {
  this->sensorName = "Luce";
}

Luce::~Luce(){}

float Luce::campiona() {
    int value = analogRead(this->pin);
    value = map(value, 0, 800, 0, 10);
    this->value = static_cast<float>(value);
    setSoglieSuccessive(this->soglia,this->value);
    return this->value;
} 
#endif
