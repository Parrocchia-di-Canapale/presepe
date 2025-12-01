#include "GenericLight.ino"

class Planet : public GenericLight{
  private:
    int transitionDuration;
  public:
    Planet(int pin, int transitionDuration = 20, bool pwm = false){
      GenericLight(pin, pwm);
    }

    int getTransitionDuration(){
      return transitionDuration;
    }

    void setTransitionDuration(int duration){
      this.transitionDuration = duration;
    }
    
    virtual void turnOn(){
      for(int i = 0; i < 256; i++){
        analogWrite(getPin(), i); //(-1.0+pow(1.022,i))
        delay(getTransitionDuration()*1000/255);
      }
    }

    virtual void turnOff(){
      for(int i = 0; i < 256; i++){
        analogWrite(getPin(), 255-i); //(-1.0+pow(1.022,i))
        delay(getTransitionDuration()*1000/255);
      }
    }
}