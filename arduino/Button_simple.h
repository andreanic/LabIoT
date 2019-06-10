#ifndef BUTTONSIMPLE_H
#define BUTTONSIMPLE_H
//KY-004
class Button_simple {
  private:
    int pin;
  public:
    Button_simple(int pin);     
    bool isPressed();
  private:
    int readValue(); 
};
Button_simple::Button_simple(int pin):pin(pin){
  pinMode(this->pin,INPUT);
} 
int Button_simple::readValue(){
  return digitalRead(this->pin);  
}
bool Button_simple::isPressed(){
  if(this->readValue() == HIGH){
    return true;  
  }  
  return false;
}
#endif
