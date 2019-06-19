#ifndef HTTPCLIENT8266
#define HTTTPCLIENT8266
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
//#include <ESP8266WiFi.h>
//#include <Arduino.h>
class HttpClient8266 {
  private:
  
  public:
    HttpClient8266();
    void doPost();
    void doGet(const String url,String &data);
};
HttpClient8266::HttpClient8266(){}
void HttpClient8266::doPost(){
    //WiFiClient wificlient;
    //HttpClient httpclient;  
}
void HttpClient8266::doGet(const String url, String &data){
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, url)) { 
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();
      if (httpCode > 0) {
        //Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          data = http.getString();
          //Serial.println(data);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
   
}

#endif
