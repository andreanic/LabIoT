#ifndef MQTTINTERFACE_H
#define MQTTINTERFACE_H

class MQTTInterface {
  public:
    MQTTInterface();
    virtual bool isConnected() =0;
    virtual bool connect() =0;
    virtual void reconnect()=0;
    virtual void publish(const char* topic, const char *msg,bool retained=false)=0;
    virtual void subscribe(const char* topic,int qos)=0;
    virtual void loop() =0;
    virtual void setCallback(void (*fp)(char*, byte*,unsigned int)) =0; 
 };
MQTTInterface::MQTTInterface(){}
#endif
