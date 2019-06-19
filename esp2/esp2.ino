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
#include <sstream>
ESP8266WiFiMulti WiFiMulti;

//LAB
char SECRET_SSID[] = "IoTLabThingsU14";        
char SECRET_PASS[] = "L@b%I0T*Ui4!P@sS**0%Less";
IPAddress ip(149, 132, 182, 46);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(149, 132, 2, 3);
IPAddress gateway(149, 132, 182, 1);
const char *mqttserver ="149.132.182.203";
ESP8266WiFiService ESP8266Wifi(ip,dns,gateway,subnet,SECRET_SSID,SECRET_PASS);
 
//CASA
/*String SECRET_SSID = "TP-LINK_4EDD0A";         
String SECRET_PASS = "215c575007228"; 
IPAddress ip(192,168,1,108);
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192,168,1,1);
const char *mqttserver ="192.168.1.102";
ESP8266WiFiService ESP8266Wifi(ip,dns,gateway,subnet,SECRET_SSID,SECRET_PASS);*/
unsigned long aliveFrequency = 30000;
unsigned long lastAliveSignal;
String webServerAddress="149.132.182.203:8080";
//String webServerAddress="149.132.182.121:3000";
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

unsigned int boardId=0;
const unsigned long heartbeatFrequency=600000;
unsigned long lastHeartBeat;
WiFiClient client;
HTTPClient http;
bool enabled=true;
    
void setup() {
  Serial.begin(9600);
  while(!Serial){}
  ESP8266Wifi.connect();
  mqtt->setCallback(callback);
  unsigned long current = millis();
  String allObjJson; 
  createJsonObj(allObjJson,boardId);
  //String request = "http://"+webServerAddress+"/testPost";
  String request = "http://"+webServerAddress+"/device/subscribe";
  int httpCode;
  String payload;
  httpPost(request,allObjJson,httpCode,payload);
  Serial.println("Rcihiesta subscribe setup");
  if(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY){
    boardId = getDeviceIdFromHttp(payload); 
    lastAliveSignal=current; 
  }
  
  Serial.println("Id board:" + String(boardId));  
  
  
}

void loop() {
  if(ESP8266Wifi.isConnected() == false){
    ESP8266Wifi.connect();  
  }
  if (!mqtt->isConnected()) {
      mqtt->reconnect();
      mqtt->subscribe("Help",1);
      mqtt->subscribe("start",1);
      mqtt->subscribe("stop",1);
  }
  mqtt->loop();
     unsigned long currentAlive = millis();
     if(currentAlive - lastAliveSignal  >= aliveFrequency){
      Serial.println("Rcihiesta subscribe loop");
      String allObjJson; 
      createJsonObj(allObjJson,boardId);
      //String request = "http://"+webServerAddress+"/testPost";
      String request = "http://"+webServerAddress+"/device/subscribe";
      int httpCode;
      String payload;
      Serial.println("tempo richiesta " + String(millis()));
      httpPost(request,allObjJson,httpCode, payload);
      if(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY){
        boardId = getDeviceIdFromHttp(payload);  
      }
      lastAliveSignal = currentAlive;
      Serial.println("Id board:" + String(boardId));
   }
  if(enabled == true){ 
    if(button->isPressed()){
        led->activate(LOW);
        ledHelp->activate(LOW);
        Serial.println("Conferma di presenza dell'infermiere");
     }
  
     if(buttonHelp->isPressed()){
        ledHelp->activate(HIGH); 
        mqtt->publish(String("aiuto").c_str(), String("Help aiutami").c_str());
        Serial.println("Richiesta di aiuto inviata");
     }
  
    //SENSORI
    long current = millis();
     if(boardId != 0) {
      String alertString="alert";
      const char* al = alertString.c_str();
      //Serial.println("Board " + String(boardId));
     if(vibration->canSense(current)){
        float valorevibrazione = vibration->campiona();
        String svib;
        StaticJsonDocument<300> doc;
        doc["deviceId"]=boardId;
        doc["sensorId"] = vibration->sensorId;
        doc["value"] = valorevibrazione;
        vibration->setUltimoCampionamento(current);
        
        if(vibration->isAlert()){
          doc["isAlert"] = true;
          serializeJson(doc,svib);
          Serial.println("alert vibrazione");
          mqtt->publish(al, svib.c_str());
        }
        else { 
          //altrimenti solo se il valore è diverso da quello precedente invia tramite mqtt
          if(oldvalue_vibrazione != valorevibrazione){
              doc["isAlert"] = false;
              serializeJson(doc,svib);
              Serial.println("dati vibrazione");
              mqtt->publish("dati",svib.c_str());
              oldvalue_vibrazione = valorevibrazione;
          }  
        }
        //Serial.print("Vibrazione: ");
        //Serial.println(valorevibrazione);
      }
      //Heartbeat
      if(heartbeat->canSense(current)){
         float valoreheart = heartbeat->campiona();
         String scuore;
         StaticJsonDocument<300> doc;
         doc["deviceId"]=boardId;
         doc["sensorId"] = heartbeat->sensorId;
         doc["value"] = valoreheart;
         heartbeat->setUltimoCampionamento(current);
          if(heartbeat->isAlert()){
            doc["isAlert"] = true;
            serializeJson(doc,scuore);
            Serial.println("Alert cuore");
            mqtt->publish(al, scuore.c_str());
          }
          else {
            //solo se il valore è diverso da quello precedente invia tramite mqtt
            if(oldvalue_heart != valoreheart){
                doc["isAlert"] = false;
                serializeJson(doc,scuore);
                Serial.println("dati cuore");
                mqtt->publish("dati", scuore.c_str());
                oldvalue_heart = valoreheart;
            }  
          }
         //Serial.println(valoreheart);
      }
      //Tilt
      if(tilt->canSense(current)){
          float valoretilt = tilt->campiona();
          String stilt;
          StaticJsonDocument<300> doc;
          doc["deviceId"]=boardId;
          doc["sensorId"] = tilt->sensorId;
          doc["value"] = valoretilt;
          serializeJson(doc,stilt);
          tilt->setUltimoCampionamento(current);
          if(tilt->isAlert()){
            doc["isAlert"] = true;
            serializeJson(doc,stilt);
            Serial.println("Alert tilt");
            
            mqtt->publish(al, stilt.c_str());
          }
          else {
            if(oldvalue_tilt != valoretilt){
              doc["isAlert"] = false;
              serializeJson(doc,stilt);
              Serial.println("dati tilt");
              mqtt->publish("dati", stilt.c_str());
              oldvalue_tilt = valoretilt;
            }  
          }
          //Serial.print("Tilt: ");
            //Serial.println(valoretilt);
      }
     }
    }
  delay(2000);
}
/*
{
 "device":{
  "deviceName":"arduino MKR 1000",
  "deviceId": 100000
 },
 "sensors":[{
  "sensorId":"KSI - 85",
  "sensorName":"Temperatura",
  "descritpion":"Sensore per misurare la temperatura"
 }]
}
*/
void createJsonObj(String &allObjJson,unsigned int board) {
  StaticJsonDocument<2048> doc;
  JsonObject root = doc.to<JsonObject>();
  JsonObject device = root.createNestedObject("device");
  device["deviceName"]="ESP8266";
  device["description"]="Dispositivo esp per monitoraggio paziente della stanza 102";
  if(board != 0){
    device["deviceId"]=board;  
  }
  else {
    JsonArray sensors = root.createNestedArray("sensors");
    heartbeat->getJsonMetadata(sensors.createNestedObject());
    tilt->getJsonMetadata(sensors.createNestedObject());
    vibration->getJsonMetadata(sensors.createNestedObject());
  }
  serializeJson(root, allObjJson);  
}

void callback(char* topic, byte* payload, unsigned int length){
  String msgPayload = String((char *)payload);
  payload[length] = '\0'; 
  int pwmVal = atoi((char *)payload);
  if(String(topic) == "start") {
    if(String(boardId) == String(pwmVal)) {
        Serial.println("Attivato");
        enabled = true;
    }
  }
  else if(String(topic)=="stop"){
    if(String(boardId) == String(pwmVal)){
        enabled = false;
        Serial.println("Disabilitato");
      }
  }
  else {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    //led->activate(HIGH);  
  }
}
void httpPost(const String requestUrl, const String &data,int &httpCode, String &payloadRequest){
    Serial.println("Indirizzo " + requestUrl);
    if (http.begin(client,requestUrl)) { 
      http.addHeader("Content-Type", "application/json"); 
      httpCode = http.POST(data);
      if (httpCode > 0) {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          payloadRequest = http.getString();
        }
      } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }   
  
unsigned int getDeviceIdFromHttp(const String &payloadRequest) {
    StaticJsonDocument<1024> doc;
    DeserializationError err = deserializeJson(doc,payloadRequest);
    if (err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
    }
    JsonObject obj = doc.as<JsonObject>();
    if (obj.containsKey("payload")) {
        JsonObject payload = obj["payload"];
        String deviceId;
        serializeJson(payload["deviceId"],deviceId);
        unsigned int boardId = deviceId.toInt();
        return boardId;
    }
    return 0;
}
