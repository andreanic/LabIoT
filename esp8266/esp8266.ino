#include "ESP8266WiFiService.h"
#include "ESP8266MQTT.h"
//#include "ServerWeb.h"
#include <ArduinoJson.h>
#include "Tilt_sensor.h"
#include "Vibration_sensor.h"
#include "Hearbeat_sensor.h"
#include "Led_actuator.h"
#include "Button_simple.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

//LAB
char SECRET_SSID[] = "IoTLabThingsU14";        
char SECRET_PASS[] = "L@b%I0T*Ui4!P@sS**0%Less";
IPAddress ip(149, 132, 182, 49);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(149, 132, 2, 3);
IPAddress gateway(149, 132, 182, 1);
const char *mqttserver ="149.132.182.121";
ESP8266WiFiService ESP8266Wifi(ip,dns,gateway,subnet,SECRET_SSID,SECRET_PASS);
 
//CASA
/*String SECRET_SSID = "TP-LINK_4EDD0A";         
String SECRET_PASS = "215c575007228"; 
IPAddress ip(192,168,1,108);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192,168,1,1);
const char *mqttserver ="192.168.1.102";
ESP8266WiFiService ESP8266Wifi(ip,dns,gateway,subnet,SECRET_SSID,SECRET_PASS);*/



MQTTInterface *mqtt = new ESP8266MQTT(mqttserver,1883);
Tilt_sensor *tilt = new Tilt_sensor(D2,1,50);
Heartbeat_sensor *heartbeat= new Heartbeat_sensor(A0,144,3000);
Vibration_sensor *vibration = new Vibration_sensor(D0,1,50);
float oldvalue_vibrazione = -1;
float oldvalue_heart = -1;
float oldvalue_tilt = -1;
//connetere un led e un button ky-004
Led_actuator *led = new Led_actuator(D1);
Led_actuator *ledHelp = new Led_actuator(D8);
Button_simple *button = new Button_simple(D3);
Button_simple *buttonHelp = new Button_simple(D7);



void setup() {
  Serial.begin(9600);
  while(!Serial){}
  mqtt->setCallback(callback);
  String allObjJson; 
  createJsonObj(allObjJson);
  //fa chiamata al web server che ritorna id
  httpPost("localhost",3000,"testPost",allObjJson);
  Serial.println(allObjJson);
}

void loop() {
  if(ESP8266Wifi.isConnected() == false){
    ESP8266Wifi.connect();  
    //serverweb.startServer();
  }
  if (!mqtt->isConnected()) {
      mqtt->reconnect();
      mqtt->subscribe("Help");
  }
  //serverweb.listen();
  mqtt->loop();
  String allObjJson; 
  createJsonObj(allObjJson);
  //fa chiamata al web server che ritorna id
  httpPost("localhost",3000,"testPost",allObjJson);
  delay(2000);
  /*if(button->isPressed()){
      led->activate(LOW);
      ledHelp->activate(LOW);
      Serial.println("Conferma di presenza dell'infermiere");
   }

   if(buttonHelp->isPressed()){
      ledHelp->activate(HIGH); 
      mqtt->publish("aiuto", "Help aiutami");
      Serial.println("Richiesta di aiuto inviata");
   }*/

  //SENSORI
  /*long current = millis();
   //Vibrazione
   if(vibration->canSense(current)){
      float valorevibrazione = vibration->campiona();
      String svib;
      StaticJsonDocument<300> doc;
      doc["sensorName"]="Vibrazione";
      doc["value"] = valorevibrazione;
      vibration->setUltimoCampionamento(current);
      
      if(vibration->isAlert()){
        doc["isAlert"] = true;
        serializeJson(doc,svib);
        Serial.println("alert vibrazione");
        mqtt->publish("alert", svib.c_str());
      }
      else { 
        //altrimenti solo se il valore è diverso da quello precedente invia tramite mqtt
        if(oldvalue_vibrazione != valorevibrazione){
            doc["isAlert"] = false;
            serializeJson(doc,svib);
            mqtt->publish("dati",svib.c_str());
            oldvalue_vibrazione = valorevibrazione;
        }  
      }
      Serial.print("Vibrazione: ");
      Serial.println(valorevibrazione);
    }
    //Heartbeat
    if(heartbeat->canSense(current)){
       float valoreheart = heartbeat->campiona();
       String scuore;
       StaticJsonDocument<300> doc;
       doc["sensorName"]="Heartbeat";
       doc["value"] = valoreheart;
       heartbeat->setUltimoCampionamento(current);
        if(heartbeat->isAlert()){
          doc["isAlert"] = true;
          serializeJson(doc,scuore);
          Serial.println("Alert cuore");
          mqtt->publish("alert", scuore.c_str());
        }
        else {
          //solo se il valore è diverso da quello precedente invia tramite mqtt
          if(oldvalue_heart != valoreheart){
              doc["isAlert"] = false;
              serializeJson(doc,scuore);
              mqtt->publish("dati", scuore.c_str());
              oldvalue_heart = valoreheart;
          }  
        }
       Serial.println(valoreheart);
    }
    //Tilt
    if(tilt->canSense(current)){
        float valoretilt = tilt->campiona();
        String stilt;
        StaticJsonDocument<300> doc;
        doc["sensorName"]="Tilt";
        doc["value"] = valoretilt;
        serializeJson(doc,stilt);
        tilt->setUltimoCampionamento(current);
        if(tilt->isAlert()){
          doc["isAlert"] = true;
          serializeJson(doc,stilt);
          Serial.println("Alert tilt");
          mqtt->publish("alert", stilt.c_str());
        }
        else {
          if(oldvalue_tilt != valoretilt){
            doc["isAlert"] = false;
            serializeJson(doc,stilt);
            mqtt->publish("dati", stilt.c_str());
            oldvalue_tilt = valoretilt;
          }  
        }
        Serial.print("Tilt: ");
          Serial.println(valoretilt);
    }*/
}
//{device: {deviceName:esp8266,deviceId:null}} prendere i valori da telegram
/*fa il json di tutti i sensori e li invia al server */
void createJsonObj(String &allObjJson) {
  StaticJsonDocument<1024> doc;
  JsonArray array = doc.to<JsonArray>();
  //aggiunere id:null
  String heartJson = heartbeat->getJsonMetadata();
  String tiltJson = tilt->getJsonMetadata();
  String vibrationJson = vibration->getJsonMetadata();
  array.add(heartJson);
  array.add(tiltJson);
  array.add(vibrationJson);
  serializeJson(doc, allObjJson);
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  led->activate(HIGH);
}
void httpPost(const String host, uint16_t port, String uri, const String &data){
    WiFiClient client;
    HTTPClient http;
    if (http.begin(client,host,port,uri)) {  
      int httpCode = http.POST(data);
      if (httpCode > 0) {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.println(String(http.getSize()));
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }   
