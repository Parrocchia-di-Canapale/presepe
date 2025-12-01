#include <LinkedList.h>

class Subject{
  private:
    LinkedList<Observer*> observers;

  public: 
    void registerObserver(Observer *o){
      observers.add(o);
    }

    void removeObserver(Observer *o){
      observers.remove(o);
    }

    virtual void notifyObservers() = 0;
}