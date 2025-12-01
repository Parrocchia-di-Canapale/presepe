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

    int getPin(){
      return this.pin;
    }

    void setPin(int pin){
      this.pin = pin;
    }

    bool getCurrentState(){
      return this.currentState;
    }

    void setCurrentState(bool state){
      currentState = state;
    }

    bool isPWM(){
      return pwm;
    }

    void setPWM(bool value){
      pwm = value;
    }

    virtual void turnOn() = 0;

    virtual void turnOff() = 0;
}