#include "esp32-hal-gpio.h"

class GenericLight{
  int pin;
  bool currentState;
  bool pwm;

  public:
    GenericLight(int pin, bool pwm = false) : pin(pin), pwm(pwm), currentState(false){
      pinMode(this.pin, OUTPUT);
      digitalWrite(this.pin, LOW);
    }

    virtual void turnOn(){
      digitalWrite(this.pin, HIGH);
      currentState = true;
    }

    virtual void turnOff(){
      digitalWrite(this.pin, LOW);
      currentState = false;
    }
}