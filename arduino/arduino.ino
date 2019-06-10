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

char serverAddress[] = "149.132.182.172";
char mqttBroker[] = "149.132.182.121";
int port = 8080;

String allObjJson;
// tempo e id di Arduino
long tempo = 0;
long idArduino = 0;

HttpClient httpClient = HttpClient(client, serverAddress, port);
//////////////Wifi
//NBmettere ip e pass della rete di labiot
//LAB
IPAddress ip(149, 132, 182, 46);  
WiFiService* wifiService = new WiFiService();
WiFiClient wificlient;
WiFiClient net; 
MQTTClient mqttClient;

//////////////////////////////////SENSORI
Luce *luce = new Luce(A0,0,30000);
Temperatura *temperatura = new Temperatura(DHT,DHT11_PIN,30,60000);
Umidita *umidita = new Umidita(DHT,DHT11_PIN,70,60000);
Umiditemp *umiditemp = new Umiditemp(DHT,DHT11_PIN);
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

  createJsonObj(allObjJson);
  postRequest(allObjJson);
  
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
  // creo JSON per i dati campionati
  createJsonObj(allObjJson);
  postRequest(allObjJson);
  
  // funz per dire se arduino è vivo  (Gabriele)
  long secondo = millis();
  // 600 volte 1000 millisecondi = 600 secondi
  if(secondo-tempo>=600 * 1000){
    postRequest();
    Serial.println("sono vivo!");
    //client.get("http://www.arduino.cc/idAssociateToArduino");

    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      idArduino = client.read();
      SerialUSB.print(idArduino);
    }
    SerialUSB.flush();
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
    postRequest(payload); 
  }
  else if(topic == "alert"){
    Serial.println("Ricevo alert");
    postRequest(payload);
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
    
    if(fuoco->canSense(current)){
        nota = 'C';
        float fuocoValue =fuoco->campiona();  
        //Serial.println("Inserisco Fuoco");
        postRequest(fuoco->getJson());
        fuoco->setUltimoCampionamento(current);
    }
    if(suono->canSense(current)){
        nota = 'c';
        float suonoValue = suono->campiona();
        //Serial.println("Inserisco Suono -> " + String(suonoValue));
        postRequest(suono->getJson());
        suono->setUltimoCampionamento(current);
    }
    if(luce->canSense(current)){
        nota = 'd';
        float luceValue=luce->campiona();
        //Serial.println("Inserisco Luce");
        postRequest(luce->getJson());
        luce->setUltimoCampionamento(current);
    }
    if(temperatura->canSense(current)){
        nota = 'e';
        float tempValue=temperatura->campiona();
        //Serial.println("Inserisco Temp");
        postRequest(temperatura->getJson());
        temperatura->setUltimoCampionamento(current);
    }
    if(umidita->canSense(current)){
        nota = 'f';
        float umidValue=umidita->campiona();
        //Serial.println("Inserisco Umidita");
        postRequest(umidita->getJson());
        umidita->setUltimoCampionamento(current);
    }
    if(wifi->canSense(current)){
        nota = 'a';
        float wifiValue= wifi->campiona();
        //Serial.println("Inserisco Wifi");
        postRequest(wifi->getJson());
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
 int tones[] = {  956, 1014, 1136, 1275, 1432,1519, 1700, 1915};
 // play the tone corresponding to the note name
 for (int i = 0; i < 8; i++) {
  if (names[i] == note) {
    playTone(tones[i], duration);
  }
 }
}

int postRequest(String data){
  String contentType = "application/json";
  //httpClient.post("/sensor/values/create", contentType, data);

  httpClient.beginRequest();
  httpClient.post("/sensor/values/create");
  httpClient.sendHeader("Content-Type", contentType);
  httpClient.sendHeader("Content-Length", data.length());
  httpClient.beginBody();
  httpClient.print(data);
  httpClient.endRequest();
  
  int statusCode = httpClient.responseStatusCode();

  // 200 (ricev success) 400 (bad request) 404 (not found) 500 (Mostrare messaggio ricevuto)
  if(statusCode == 200){
    // prendo il Json e prendo l'id di arduino e glielo metto
    httpClient.get("http://www.arduino.cc/idAssociateToArduino"); // cambiare con link web server.
    JsonObject obj = client.read();
    idArduino = obj["deviceId"];
  } else if(statusCode == 400){
    Serial.print("Errore 400!");
  } else if(statusCode == 404){
    Serial.print("Non Trovato Error 404");
  } else if(statusCode == 500){
    JsonObject obj = httpClient.get("http://www.arduino.cc/idAssociateToArduino");
    serializeJson(obj, Serial);
  }
  return statusCode;
}


void createJsonObj(String &allObjJson) {
  StaticJsonDocument<1024> doc;
  //JsonArray array = doc.to<JsonArray>();
  String luceJson = luce->getJsonMetadata();
  String umiditempJson = umiditemp->getJsonMetadata();
  String suonoJson = suono->getJsonMetadata();
  String wifiJson = wifi->getJsonMetadata();
  String fuocoJson = fuoco->getJsonMetadata();
  array.add(luceJson);
  array.add(umiditempJson);
  array.add(suonoJson);
  array.add(wifiJson);
  array.add(fuocoJson);
  array.add("deviceId:\""+idArduino+"\"");
  serializeJson(doc, allObjJson);
}

// fare una funzione che prende device {device: {deviceName:"arduino MKR 1000",deviceId:"100000"}} 

void createJsonObjDevice(String &allObjJson) {
  StaticJsonDocument<1024> doc;
  //JsonArray array = doc.to<JsonArray>();
  String luceJson = luce->getJsonMetadata();
  String umiditempJson = umiditemp->getJsonMetadata();
  String suonoJson = suono->getJsonMetadata();
  String wifiJson = wifi->getJsonMetadata();
  String fuocoJson = fuoco->getJsonMetadata();
  array.add(luceJson);
  array.add(umiditempJson);
  array.add(suonoJson);
  array.add(wifiJson);
  array.add(fuocoJson);
  array.add("deviceId:\""+idArduino+"\"");
  serializeJson(doc, allObjJson);
}
