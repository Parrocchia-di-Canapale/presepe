#include "GenericLight.h"

class Planet : public GenericLight{
  private:
    int transitionDuration;
  public:
    Planet(int pin, int t = 20, bool pwm = true) : GenericLight(pin, pwm), transitionDuration(t){}

    int getTransitionDuration(){
      return transitionDuration;
    }

    void setTransitionDuration(int duration){
      transitionDuration = duration;
    }
    
    virtual void turnOn(){
      if(isPWM()){
        for(int i = 0; i < 256; i++){
          analogWrite(getPin(), i); //(-1.0+pow(1.022,i))
          delay(getTransitionDuration()*1000/255);
          setCurrentState(true);
        }
      }else {
        delay(getTransitionDuration()*1000);
        digitalWrite(getPin(), HIGH);
        setCurrentState(true);
      }
    }

    virtual void turnOff(){
      if(isPWM()){
        for(int i = 0; i < 256; i++){
          analogWrite(getPin(), 255-i); //(-1.0+pow(1.022,i))
          delay(getTransitionDuration()*1000/255);
        }
        setCurrentState(false);
      }else{
        delay(getTransitionDuration()*1000);
        digitalWrite(getPin(), LOW);
        setCurrentState(false);
      }
    }
};