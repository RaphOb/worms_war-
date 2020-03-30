//
// Created by oraph on 30/03/2020.
//

#ifndef LITTLEBIGGAME_EVENTOBSERVABLE_HH
#define LITTLEBIGGAME_EVENTOBSERVABLE_HH


#include <list>
#include "../IObservable.hh"
#include "../IObserver.hh"
#include "../Direction.hh"


//enum class TypeEvent {
//    RIGHT = 0, LEFT = 1, JUMP = 2, FIRE = 3
//};
//class IObservable

class EventObservable : public IObservable {
public:
    void addObserver(IObserver*) override;
    void removeObserver(IObserver*) override;
    void notify(Direction) override ;
    void update();

private:
    std::list<IObserver *> observers;
};


#endif //LITTLEBIGGAME_EVENTOBSERVABLE_HH
