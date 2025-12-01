#include "GenericLight"
#include "Subject.ino"

class House : public GenericLight, public Subject{
  public:
    House(int pin){
      GenericLight(pin);
    }

    virtual void turnOn() override{
      digitalWrite(getPin(), true);
      setCurrentState(true);
    }

    virtual void turnOff() override{
      digitalWrite(getPin(), LOW)
      setCurrentState(false);
    }

    void notifyObservers() override{
      
    }

}