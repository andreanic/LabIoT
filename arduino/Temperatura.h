#ifndef TEMPERATURA_H
#define TEMPERATURA_H
#include <dht11.h>
#include "Sensor.h"
class Temperatura: public Sensor {
//controllare valori di soglia anche umidita
	private:
		 dht11 dht;
	public:
		Temperatura(dht11 dht, int pin,float soglia);
    Temperatura(dht11 dht, int pin,float soglia,unsigned long frequenzacampionamento);
    ~Temperatura();
    Temperatura(const Temperatura& other);
    Temperatura& operator=(const Temperatura &other);
		float campiona();
};

Temperatura::Temperatura(dht11 dht,int pin,float soglia): Sensor(pin,soglia){
	this->dht = dht;
  this->sensorId = "KY‐015";
  this->sensorName = "sensore umidità e temperatura";
  this->description="sensore per misurare l'umidità e la temperatura dell'ambiente";
  this->uom="gradi centigradi e %";
  this->typeValue="Float";
  this->isDigital=true;
  this->url="";
}
Temperatura::Temperatura(dht11 dht,int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento){
  this->dht = dht;
  this->sensorId = "KY‐015";
  this->sensorName = "sensore umidità e temperatura";
  this->description="sensore per misurare l'umidità e la temperatura dell'ambiente";
  this->uom="gradi centigradi e %";
  this->typeValue="Float";
  this->isDigital=true;
  this->url="";
}
Temperatura::~Temperatura(){}

Temperatura::Temperatura(const Temperatura& other): Sensor(other){
    this->dht = other.dht;
}
Temperatura& Temperatura::operator=(const Temperatura &other){
  if(this != &other){
      Sensor::operator=(other);
      this->dht = other.dht;
  }
  return *this;
}

float Temperatura::campiona(){
   int chk = this->dht.read(this->pin);
   int temperatura = this->dht.temperature;
   this->value = static_cast<float>(temperatura);
   setSoglieSuccessive(this->value,this->soglia);
   return this->value;
}
#endif
