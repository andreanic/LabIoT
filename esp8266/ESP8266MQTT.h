#ifndef ESP8266MQTT_H
#define ESP8266MQTT_H
#include <ESP8266WiFi.h>
#include "MQTTInterface.h"
#include <PubSubClient.h>

class ESP8266MQTT : public MQTTInterface {
  private:
    const char* server;
    unsigned int port;
    PubSubClient client;
    long lastMsg = 0;
    char msg[50];
    int value = 0;
  public:
    ESP8266MQTT(const char* server,int port);
    bool isConnected() override;
    bool connect() override;
    void reconnect() override;
    void publish(const char* topic, const char *msg) override;
    void subscribe(const char* topic) override;
    void setCallback(void (*fp)(char*, byte*,unsigned int)) override;
    void loop();
};
ESP8266MQTT::ESP8266MQTT(const char* server,int port):server(server),port(port){
  WiFiClient espClient;
  PubSubClient pubsubc(espClient);
  this->client = pubsubc;
  this->client.setServer(this->server, this->port);
}
bool ESP8266MQTT::isConnected() {
  return this->client.connected();  
}
bool ESP8266MQTT::connect(){
  return this->client.connect(this->server);  
}
void ESP8266MQTT::publish(const char* topic, const char *msg){
  this->client.publish(topic,msg);
}
void ESP8266MQTT::subscribe(const char* topic) {
  this->client.subscribe(topic);
}
void ESP8266MQTT::reconnect() {
  while (!this->isConnected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (this->connect()) {
      Serial.println("connesso al broker");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void ESP8266MQTT::loop() {
  this->client.loop(); 
}

void ESP8266MQTT::setCallback(void (*fp)(char*, byte*,unsigned int)){
  this->client.setCallback(fp);
}
#endif
