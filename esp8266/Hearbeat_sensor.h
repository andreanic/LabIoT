#ifndef HEARTBEAT_H
#define HEARTBEAT_H
#include "Sensor.h"

class Heartbeat_sensor: public Sensor {
  public:
    Heartbeat_sensor(int pin,float soglia);
    Heartbeat_sensor(int pin,float soglia,unsigned long frequenzacampionamento);
    ~Heartbeat_sensor();
    float campiona();
};

Heartbeat_sensor::Heartbeat_sensor(int pin,float soglia): Sensor(pin,soglia) {
        sensorName="heartbeat";
        description="sensore cherileva i battiti del cuore";
        um = "";
        typeValue="string";
        digitOrAnal="float";
        url="";
}
Heartbeat_sensor::Heartbeat_sensor(int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento) {
        description="sensore cherileva i battiti del cuore";
        um = "";
        typeValue="string";
        digitOrAnal="float";
        url="";
}

Heartbeat_sensor::~Heartbeat_sensor(){
        description="sensore cherileva i battiti del cuore";
        um = "";
        typeValue="string";
        digitOrAnal="float";
        url="";
  }

float Heartbeat_sensor::campiona() {
  double alpha = 0.75;
  int period = 3000;
  double change = 0.0;
  double minval = 0.0;
  double oldValue = 0;
  double oldChange = 0;
 
 int valoregrezzo = analogRead(this->pin);
 double valorepulito = alpha * oldValue + (1 - alpha) * valoregrezzo;
 this->value = static_cast<float>(valorepulito);
 setSoglieSuccessive(this->value,this->soglia);
 return this->value;

} 
#endif
