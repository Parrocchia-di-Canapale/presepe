#include <LinkedList.h>

class Observer{
  private:
    LinkedList<Subject*> subjects;

  public:
    Observer(Subject* s){
      subjects.add(s);
      s->registerObserver(this);
    }

    Observer(LinkedList<Subject>* list){
      for(auto itr = list.std::begin(); itr != list.std::end(); itr++){
        subjects.add(this);
        (*itr)->registerObserver(this);
      }
    }

    virtual ~Observer(){
      for(auto itr = list.std::begin(); itr != list.std::end(); itr++){
        subjects.remove(this);
        (*itr)->removeObserver(this);
      }
    }

    virtual void update() = 0;

}