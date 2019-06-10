#ifndef UMIDITA_H
#define UMIDITA_H
#include <dht11.h>
#include "Sensor.h"
class Umidita: public Sensor {
	private:
		dht11 dht;
	public:
		Umidita(dht11 dht, int pin,float soglia);
    Umidita(dht11 dht, int pin,float soglia,unsigned long frequenzacampionamento);
		~Umidita();
    Umidita(const Umidita& other);
    Umidita& operator=(const Umidita &other);
		float campiona();
};

Umidita::Umidita(dht11 dht, int pin,float soglia): Sensor(pin,soglia){
	this->dht = dht;
  this->sensorId = "KY‐015";
  this->sensorName = "sensore umidità e temperatura";
  this->description="sensore per misurare l'umidità e la temperatura dell'ambiente";
  this->uom="gradi centigradi e %";
  this->typeValue="Float";
  this->isDigital=true;
  this->url="";
}
Umidita::Umidita(dht11 dht, int pin,float soglia,unsigned long frequenzacampionamento): Sensor(pin,soglia,frequenzacampionamento){
  this->dht = dht;
  this->sensorId = "KY‐015";
  this->sensorName = "sensore umidità e temperatura";
  this->description="sensore per misurare l'umidità e la temperatura dell'ambiente";
  this->uom="gradi centigradi e %";
  this->typeValue="Float";
  this->isDigital=true;
  this->url="";
}
Umidita::~Umidita(){}

Umidita::Umidita(const Umidita& other): Sensor(other){
  this->dht = other.dht;  
}
Umidita& Umidita::operator=(const Umidita &other){
  if(this != &other){
      Sensor::operator=(other);
      this->dht = other.dht;
  }
  return *this;  
}

float Umidita::campiona() {
  int chk = this->dht.read(this->pin);
  int umidita = this->dht.humidity;
  this->value = static_cast<float>(umidita);
  setSoglieSuccessive(this->value,this->soglia);
  return this->value;
}
#endif
