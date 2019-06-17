////////////Librerie
//LAB
#include <WiFi101.h> 
#include <SPI.h>
#include <MQTT.h>
#include "rgb_lcd.h"
#include <dht11.h>
#include <ArduinoHttpClient.h>
#include "Luce.h"
#include "Temperatura.h"
#include "Umidita.h"
#include "Fuoco.h"
#include "Wifi.h"
#include "Suono.h"
#include "WiFiService.h"
#include "Button_simple.h"
////////variabili/costanti
const int pinBuzzer = 0;
#define DHT11_PIN 4
dht11 DHT;
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 255;
const int colorB = 255;

int status = WL_IDLE_STATUS;
WiFiClient client ;

//String serverAddress="149.132.182.203";
//String webServerAddress="149.132.182.203:8080";
String webServerAddress="149.132.182.121";
char serverAddress[] = "149.132.182.121";
char mqttBroker[] = "149.132.182.121";
IPAddress ip(149, 132, 182, 46);
int port = 3000;

String allObjJson;
unsigned int boardId =0;
// tempo e id di Arduino
long tempo = 0;
long idArduino = 0;

HttpClient httpClient = HttpClient(client, serverAddress, port);
//String request = "http://"+webServerAddress+"/device/subscribe";
String request = "http://"+webServerAddress+"/testPost";
String datiPath="";
//////////////Wifi
WiFiService* wifiService = new WiFiService();
WiFiClient wificlient;
WiFiClient net; 
MQTTClient mqttClient;

//////////////////////////////////SENSORI
Luce *luce = new Luce(A0,0,30000);
Temperatura *temperatura = new Temperatura(DHT,DHT11_PIN,30,60000);
Umidita *umidita = new Umidita(DHT,DHT11_PIN,70,60000);
Suono *suono = new Suono(A2,96,1000);
Wifi *wifi = new Wifi(15000);
Fuoco *fuoco = new Fuoco(A5,HIGH,1000);
Button_simple *button = new Button_simple(3);

int pinButton = 10;
bool doSense = true;
char nota='c';

void setup() {
  Serial.begin(115200);
  pinMode(pinBuzzer, OUTPUT);
  mqttClient.begin(mqttBroker, net);
  mqttClient.onMessage(messageReceived);
  mqttClient.loop();
  if (!mqttClient.connected()) {
    connect();
  }
  String allObjJson;
  createJsonObj(allObjJson,boardId);
  String payload;
  int statuscode = postRequest(allObjJson,request,payload);  
  if(statuscode == 200){
    getDeviceId(payload);
  }
}

void loop() {
  
  mqttClient.loop();
  if (!mqttClient.connected()) {
    connect();
  }

  campionaDati();
  if(button->isPressed()){
    Serial.println("RICHIESTA AIUTO ACCETTATA");
    mqttClient.publish("Help", "richiesta in soccorso"); 
    delay(20); 
  }
  
  // funz per dire se arduino è vivo  (Gabriele)
  long secondo = millis();
  if(secondo-tempo>=2000){
    Serial.println("sono vivo!");
    String allObjJson;
    createJsonObj(allObjJson,boardId);
    String payload;
    int statuscode = postRequest(allObjJson,request,payload);  
    if(statuscode == 200){
      getDeviceId(payload);
    }
    tempo = secondo;
  }
  
}

void messageReceived(String &topic, String &payload) {
  Serial.println("Payload -> " + payload);
  if(topic ==  "aiuto"){
    Serial.println("Ricevo aiuto");
    playNote('C',500);
  }
  else if(topic == "dati"){
    Serial.println("Ricevo dati");
    //postRequest(payload);
  }
  else if(topic == "alert"){
    Serial.println("Ricevo alert");
    //postRequest(payload);
    playNote('d',500);
  }
}

void connect(){
  Serial.println("Connecting to wifi");
  wifiService->connect(ip);
  Serial.println("Connecting client");
  while (!mqttClient.connect("arduino")) {
    Serial.print(".");
    delay(50);
  }
  Serial.println("\nSubscribing");
  mqttClient.subscribe("dati");
  mqttClient.subscribe("alert");
  mqttClient.subscribe("aiuto");
}

void campionaDati(){
    unsigned long current = millis();
    String payloadDati;
    if(fuoco->canSense(current)){
        nota = 'C';
        float fuocoValue =fuoco->campiona();  
        //Serial.println("Inserisco Fuoco");
        postRequest(fuoco->getJson(),request,payloadDati);
        fuoco->setUltimoCampionamento(current);
    }
    if(suono->canSense(current)){
        nota = 'c';
        float suonoValue = suono->campiona();
        //Serial.println("Inserisco Suono -> " + String(suonoValue));
        postRequest(suono->getJson(),request,payloadDati);
        suono->setUltimoCampionamento(current);
    }
    if(luce->canSense(current)){
        nota = 'd';
        float luceValue=luce->campiona();
        //Serial.println("Inserisco Luce");
        postRequest(luce->getJson(),datiPath,payloadDati);
        luce->setUltimoCampionamento(current);
    }
    if(temperatura->canSense(current)){
        nota = 'e';
        float tempValue=temperatura->campiona();
        //Serial.println("Inserisco Temp");
        //postRequest(temperatura->getJson(),datiPath);
        temperatura->setUltimoCampionamento(current);
    }
    if(umidita->canSense(current)){
        nota = 'f';
        float umidValue=umidita->campiona();
        //Serial.println("Inserisco Umidita");
        //postRequest(umidita->getJson(),datiPath);
        umidita->setUltimoCampionamento(current);
    }
    if(wifi->canSense(current)){
        nota = 'a';
        float wifiValue= wifi->campiona();
        //Serial.println("Inserisco Wifi");
        //postRequest(wifi->getJson(),datiPath);
        wifi->setUltimoCampionamento(current);
    }
}

void playBuzzer(){
  playNote(nota,500);
}

void playTone(int tone, int duration) {
 for (long i = 0; i < duration; i +=1) {
   digitalWrite(pinBuzzer, HIGH);
   delayMicroseconds(tone);
   digitalWrite(pinBuzzer, LOW);
   delayMicroseconds(tone);
 }
}

void playNote(char note, int duration) {
 char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
 int tones[] = { 956, 1014, 1136, 1275, 1432,1519, 1700, 1915};
 // play the tone corresponding to the note name
 for (int i = 0; i < 8; i++) {
  if (names[i] == note) {
    playTone(tones[i], duration);
  }
 }
}

int postRequest(String data,String path,String &response){
  String contentType = "application/json";
  Serial.println("in invio ...");
  Serial.println(data);
  httpClient.beginRequest();
  httpClient.sendHeader("Content-Type", contentType);
  httpClient.sendHeader("Content-Length", data.length());
  httpClient.post(path, contentType, data);
  httpClient.beginBody();
  httpClient.print(data);
  httpClient.endRequest();
  int statusCode = httpClient.responseStatusCode();
  Serial.println(String(statusCode));

/*int successo = 200;
  int badreq = 400;
  int notfound = 404;
  int mostramsg = 500;*/
  // 200 (ricev success) 400 (bad request) 404 (not found) 500 (Mostrare messaggio ricevuto)
  if(statusCode == 200){
    Serial.println("Success 200");
    response = httpClient.responseBody();
  } else if(statusCode == 400){
    Serial.println("Errore 400!");
  } else if(statusCode == 404){
    Serial.println("Non Trovato, Errore 404");
  } else if(statusCode == 500){
   /* String response = httpClient.responseBody();
    StaticJsonDocument<200> obj;
    deserializeJson(obj, response);
    serializeJson(obj["payload"], Serial);
    Serial.println("Errore 500");*/
  }
  return statusCode;
}

void getDeviceId(const String &payload ){
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    JsonObject obj = doc.as<JsonObject>();
    if (obj.containsKey("payload")) {
        JsonObject payload = obj["payload"];
        String deviceId;
        serializeJson(payload["deviceId"],deviceId);
        boardId = deviceId.toInt();
        Serial.println("Board" + String(boardId));
    }
    
    Serial.print("ID: ");
    Serial.println(boardId);  
}


void createJsonObj(String &allObjJson,unsigned int board) {
  StaticJsonDocument<1024> doc;
  JsonObject root = doc.to<JsonObject>();
  JsonObject device = root.createNestedObject("device");
  device["deviceName"]="MKR1000";
  if(board != 0){
    device["deviceId"]=board;  
  }
  JsonArray sensors = root.createNestedArray("sensors");
  luce->getJsonMetadata(sensors.createNestedObject());
  umidita->getJsonMetadata(sensors.createNestedObject());
  temperatura->getJsonMetadata(sensors.createNestedObject());
  suono->getJsonMetadata(sensors.createNestedObject());
  wifi->getJsonMetadata(sensors.createNestedObject());
  fuoco->getJsonMetadata(sensors.createNestedObject());
  serializeJson(root, allObjJson);
}
