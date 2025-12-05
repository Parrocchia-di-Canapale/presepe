#include "GenericLight.h"

class House : public GenericLight{
  public:
    House() : GenericLight(0){}

    House(int p) : GenericLight(p){}

    virtual void turnOn() override{
      digitalWrite(getPin(), true);
      setCurrentState(true);
    }

    virtual void turnOff() override{
      digitalWrite(getPin(), LOW);
      setCurrentState(false);
    }
};