#ifndef LEDACTUATOR_H
#define LEDACTUATOR_H
#include <assert.h>
class Led_actuator {
  private:
    int pin;
  public:
    Led_actuator(int pin);
    void activate(int val);
    int getPin();
};
Led_actuator::Led_actuator(int pin):pin(pin) {
  pinMode(this->pin,OUTPUT);  
}
void Led_actuator::activate(int val) {
    assert(val < 2);
    assert(val > -1);
    digitalWrite(this->pin,val);
}
int Led_actuator::getPin(){
  return this->pin;  
}
#endif
