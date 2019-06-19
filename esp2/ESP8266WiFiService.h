#ifndef ESP8266WIFISERVICE_H
#define ESP8266WIFISERVICE_H
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <SPI.h>

class ESP8266WiFiService {
  private:
    IPAddress ip;
    IPAddress dns;
    IPAddress gateway;
    IPAddress subnet;  
    String ssid;
    String pass;
   
  public:
    ESP8266WiFiService(IPAddress ip, IPAddress gateway, IPAddress subnet, String ssid,String pass);
    ESP8266WiFiService(IPAddress ip,IPAddress dns, IPAddress gateway, IPAddress subnet,String ssid,String pass);
    void config();
    void begin();
    void connect();
    String getStatus();
    bool isConnected();
};

ESP8266WiFiService::ESP8266WiFiService(IPAddress ip, IPAddress gateway, IPAddress subnet, String ssid,String pass)
  :ip(ip),gateway(gateway),subnet(subnet),ssid(ssid),pass(pass){}

ESP8266WiFiService::ESP8266WiFiService(IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet, String ssid,String pass)
  :ip(ip), dns(dns),gateway(gateway),subnet(subnet),ssid(ssid),pass(pass){}

void ESP8266WiFiService::config(){
  if(dns){
      WiFi.config(this->ip,this->dns,this->gateway,this->subnet);  
  }
  else {
    WiFi.config(this->ip, this->gateway, this->subnet);  
  }
}

void ESP8266WiFiService::begin(){
   WiFi.begin(this->ssid.c_str(),this->pass.c_str());
}

void ESP8266WiFiService::connect() {
  if(this->isConnected() == false){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(this->ssid);
    while(WiFi.status() != WL_CONNECTED){
      this->begin(); 
      this->config();
      WiFi.mode(WIFI_STA);      
      Serial.print(".");
      delay(5000);     
    }
  Serial.println("\nConnected");
  Serial.println(this->getStatus());
  }
}

String ESP8266WiFiService::getStatus(){
  String statuswifi = "SSID: " + WiFi.SSID() + "\n"; 
  statuswifi.concat("IP Address: "+ WiFi.localIP().toString()+ "\n");
  statuswifi.concat("signal strength (RSSI): " + (String)WiFi.RSSI() + " dBm \n" + WiFi.macAddress());
  return statuswifi;
}
bool ESP8266WiFiService::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}
#endif
