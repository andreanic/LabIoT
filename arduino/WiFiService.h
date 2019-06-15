#ifndef WIFISERVICE_H
#define WIFISERVICE_H
#include <WiFi101.h>

class WiFiService{
  private: 
    String ssid = "IoTLabThingsU14";         
    String pass = "L@b%I0T*Ui4!P@sS**0%Less"; 

  public:
    void connect(IPAddress ip);
    
};

void WiFiService::connect(IPAddress ip){
   IPAddress dns(149, 132, 2, 3);    
   IPAddress gateway(149, 132, 182, 1);  
   IPAddress mask(255, 255, 255, 0);  
   
   if(WiFi.status() != WL_CONNECTED){
    WiFi.config(ip, dns, gateway, mask);

    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(this->ssid, this->pass); 
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected");
  }
}
#endif
