#include <LinkedList.h>
#include "Observer.ino"

class Neighborhood{
  private:
    LinkedList<House> houses;

    LinkedList<House> awakeHouses;
    LinkedList<House> sleepingHouses;
    
  public:
    Neighborhood(){
      houses = LinkedList<House>;
    }

    void addHouse(House h){
      houses.add(h);
    }

    int getHousesNumber(){
      return houses.size();
    }

    bool turnOnRandomHouse(){

    }
}