#ifndef SENSOR_H
#define SENSOR_H
#include <ArduinoJson.h>
//#include <Time.h>
class Sensor {
    protected:
        int pin;
        float soglia;
        float value;
// NUOVI CAMPI (Gabriele)
        String sensorName;
        String description;
        String uom;
        String typeValue;
        String digitOrAnal;
        String url;

        unsigned long ultimocampionamento;
        unsigned long frequenzacampionamento;
        public: unsigned int soglieSuccessive;
        public: int maxSoglieSuccessive;
    public:
        Sensor();
        Sensor(int pin,float soglia);
        Sensor(int pin,float soglia,unsigned long frequenzacampionamento);
        ~Sensor();
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
        String getJson();
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

String Sensor::getJson(){
  DynamicJsonDocument doc(1024);
  doc["sensorName"] = this->sensorName;
  doc["value"] = this->value;
  doc["isAlert"]=this->isAlert();
  char json[1024];
  serializeJson(doc, json);

  return String(json);
}

String Sensor::getJsonMetadata(){
  DynamicJsonDocument doc(1024);
  doc["sensorName"] = this->sensorName;
  // aggiunti campi al json per ogni sensore  (Gabriele)
  // descrizione, unità di misura, tipo del valore ritornato,analogico o digitale, timestamp, url pagina sensore  (Gabriele) 
  doc["description"]=this->description;
  doc["um"]=this->um;
  doc["typeValue"]=this->typeValue;
  doc["da"]=this->digitOrAnal;
  doc["timestamp"]=this->millis();
  doc["url"]=this->url;
  doc["freqCamp"]=this->frequenzacampionamento;
  char json[1024];
  serializeJson(doc, json);

  return String(json);
}
#endif
