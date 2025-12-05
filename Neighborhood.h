#include <stdlib.h>
#include <LinkedList.h>

class Neighborhood{
  private:
    LinkedList<House> houses = LinkedList<House>();
    LinkedList<House> sleepingHouses = LinkedList<House>();
    LinkedList<House> awakeHouses = LinkedList<House>();

    int minDelay;
    int maxDelay;

  public:
    Neighborhood(int minDelay = 500, int maxDelay = 2500) : minDelay(minDelay), maxDelay(maxDelay){}

    void addHouse(House h){
      h.turnOff();
      houses.add(h);
      sleepingHouses.add(h);
    }

    int getHousesNumber(){
      return houses.size();
    }

    int getMinDelay(){
      return this->minDelay;
    }

    void setMinDelay(int minDelay){
      this->minDelay = minDelay;
    }

    int getMaxDelay(){
      return this->maxDelay;
    }

    void setMaxDelay(int maxDelay){
      this->maxDelay = maxDelay;
    }


    void turnOnHouses(){
      while(sleepingHouses.size() != 0){
        int index = random(0, sleepingHouses.size());
        sleepingHouses[index].turnOn();
        awakeHouses.add(sleepingHouses[index]);
        sleepingHouses.remove(index);
        delay(random(500, 2500));
      }
    }

    void turnOffHouses(){
      while(awakeHouses.size() != 0){
        int index = random(0, awakeHouses.size());
        awakeHouses[index].turnOff();
        sleepingHouses.add(awakeHouses[index]);
        awakeHouses.remove(index);
        delay(random(500, 2500));
      }
    }
};