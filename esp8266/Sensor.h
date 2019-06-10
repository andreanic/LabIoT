#ifndef SENSOR_H
#define SENSOR_H
#include <ArduinoJson.h>
class Sensor {
    protected:
        int pin;
        float soglia;
        float value;
        unsigned long ultimocampionamento;
        unsigned long frequenzacampionamento;
        String sensorId;
        String sensorName;
        String description;
    public: 
        unsigned int soglieSuccessive;
        int maxSoglieSuccessive;
    public:
        Sensor();
        Sensor(int pin,float soglia);
        Sensor(int pin,float soglia,unsigned long frequenzacampionamento);
        virtual ~Sensor();
        Sensor(const Sensor& other);
        Sensor& operator=(const Sensor &other);
        float getValue();
        float getSoglia();
        void setSoglia(float soglia);
        virtual float campiona()=0;
        long getUltimoCampionamento();
        void setUltimoCampionamento(unsigned long camp);
        long getFrequenza();
        void setFrequenza(unsigned long freq);
        bool canSense(unsigned long current);
        String toString(String msg, int value,String unitamisura);
        void setSoglieSuccessive(float value,float soglia);
        boolean isAlert();
        void setMaxSoglie(int n);
        String getJsonMetadata();
};

Sensor::Sensor(){
    this->pin = -1;
    this->soglia = -1;
    this->ultimocampionamento=0;
    this->frequenzacampionamento=10000;
    this->soglieSuccessive = 0;
    this->maxSoglieSuccessive = 3;
  }
Sensor::Sensor(int pin,float soglia){
    pinMode(pin,INPUT);
    this->pin = pin;
    this->soglia = soglia;
    this->ultimocampionamento =0;
    this->frequenzacampionamento = 10000;
    this->soglieSuccessive = 0;
    this->maxSoglieSuccessive = 3;
}
Sensor::Sensor(int pin,float soglia,unsigned long frequenzacampionamento) {
    pinMode(pin,INPUT);
    this->pin = pin;
    this->soglia = soglia;
    this->ultimocampionamento =0;
    this->frequenzacampionamento = frequenzacampionamento;
    this->soglieSuccessive = 0;
    this->maxSoglieSuccessive = 3;
}
Sensor::~Sensor(){}
Sensor& Sensor::operator=(const Sensor &other){
  if(this != &other){
    this->pin = other.pin;
    this->soglia = other.soglia;
    this->ultimocampionamento=other.ultimocampionamento;
    this->frequenzacampionamento=other.frequenzacampionamento;
    this->soglieSuccessive = other.soglieSuccessive;
    this->maxSoglieSuccessive = other.maxSoglieSuccessive;
  }
  return *this;  
}
Sensor::Sensor(const Sensor& other) {
  this->pin = other.pin;
  this->soglia = other.soglia;
  this->ultimocampionamento=other.ultimocampionamento;
  this->frequenzacampionamento = other.frequenzacampionamento; 
  this->soglieSuccessive = other.soglieSuccessive;
  this->maxSoglieSuccessive = other.maxSoglieSuccessive;
}

float Sensor::getValue() {
  return this->value;  
}

float Sensor::getSoglia() {
  return this->soglia;  
}

void Sensor::setSoglia(float soglia){
  this->soglia = soglia;  
}

long Sensor::getUltimoCampionamento(){
  return this->ultimocampionamento;  
}
void Sensor::setUltimoCampionamento(unsigned long camp){
  this->ultimocampionamento = camp;  
}
long Sensor::getFrequenza(){
  return this->frequenzacampionamento;
}
void Sensor::setFrequenza(unsigned long freq){
  this->frequenzacampionamento = freq;
}
bool Sensor::canSense(unsigned long current) {
  return (current - this->ultimocampionamento > frequenzacampionamento || this->ultimocampionamento == 0);  
}
String Sensor::toString(String msg, int value,String unitamisura){
  String stringa = msg;
  stringa.concat(String(value));
  stringa.concat(unitamisura);
  return stringa;
}
void Sensor::setSoglieSuccessive(float value,float soglia){
    if(value >= soglia){
      this->soglieSuccessive=this->soglieSuccessive + 1;  
    }
    else {
      this->soglieSuccessive =0;  
    }
 }
boolean Sensor::isAlert(){
    return this->soglieSuccessive >= maxSoglieSuccessive;
}
void Sensor::setMaxSoglie(int n){
  this->maxSoglieSuccessive = n;  
}
String Sensor::getJsonMetadata(){
  DynamicJsonDocument doc(1024);
  doc["sensorId"]=this->sensorId;
  doc["sensorName"] = this->sensorName;
  doc["description"] = this->description;
  char json[1024];
  serializeJson(doc, json);
  return String(json);
}
#endif
