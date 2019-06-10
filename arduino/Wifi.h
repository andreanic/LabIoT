#ifndef WIFIPOWER_H
#define WIFIPOWER_H
#include <WiFi101.h>
#include "Sensor.h"
class Wifi: public Sensor{
  public:
    Wifi();
    Wifi(unsigned long frequenzacampionamento);
    ~Wifi();
    float campiona();
    void printWifiStatus();
    sensorName = "WiFi"
    description="potenza del segnale del wifi";
    uom="decibel";
    typeValue="Float";
    digitOrAnal="Digitale";
    url="";
};

Wifi::Wifi():Sensor(){}
Wifi::Wifi(unsigned long frequenzacampionamento):Sensor(){
  this->frequenzacampionamento = frequenzacampionamento;  
  this->sensorName = "Wifipower";
}

Wifi::~Wifi(){}

float Wifi::campiona() {
  long rssi = WiFi.RSSI();
  this->value = static_cast<float>(rssi);
  setSoglieSuccessive(-60,this->value);
  return this->value;
}

void Wifi::printWifiStatus(){
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.print("signal strength (RSSI):");
  Serial.print(this->getValue());
  Serial.println(" dBm");
}
#endif
