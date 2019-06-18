#ifndef LUCE_H
#define LUCE_H
#include "Sensor.h"
class Luce: public Sensor {
  public:
    Luce(int pin,float soglia);
    Luce(int pin,float soglia,unsigned long frequenzacampionamento);
    ~Luce();
    float campiona();
};

Luce::Luce(int pin,float soglia): Sensor(pin,soglia) {
  this->sensorId="GROVE LIGHT SENSOR";
  this->sensorName="sensore di luce";
  this->description="sensore che misura la luce nell\'ambiente";
  this->uom="";
  this->typeValue="Float";
  this->isDigital=false;
  this->url="http://wiki.seeedstudio.com/Grove-Light_Sensor/";
}
Luce::Luce(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento) {
  this->sensorId="GROVE LIGHT SENSOR";
  this->sensorName="sensore di luce";
  this->description="sensore che misura la luce nell\'ambiente";
  this->uom="";
  this->typeValue="Float";
  this->isDigital=false;
  this->url="http://wiki.seeedstudio.com/Grove-Light_Sensor/";
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
