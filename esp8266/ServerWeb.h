#ifndef SERVERWEB_H
#define SERVERWEB_H
#include <ESP8266WiFi.h>
class ServerWeb {
  private:
    WiFiServer server;
  public:
    ServerWeb();
    ServerWeb(WiFiServer sever); 
    void startServer(); 
    void listen();
};
ServerWeb::ServerWeb(WiFiServer server):server(server){}
void ServerWeb::startServer(){
    this->server.begin();
  }

void ServerWeb::listen(){
 WiFiClient client = this->server.available();   
 if (client) {                             
    Serial.println("new client");           
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();           
        Serial.write(c);                    
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Click <a href=\"/H\">here</a> turn the Built in LED on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the Built in LED off<br>");
            client.println();
            break;
          }
          else {      
            currentLine = "";
          }
        }
        else if (c != '\r') {    
          currentLine += c;     
        }
        if (currentLine.endsWith("GET /H")) {
          
        }
        if (currentLine.endsWith("GET /L")) {
          
        }
      }
    }
    client.stop();
    Serial.println("client disonnected");
  }  
}
#endif
