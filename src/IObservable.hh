//
// Created by geoff on 04/02/2020.
//

#ifndef LITTLEBIGAME__EVENTOBSERVABLE_HH
#define LITTLEBIGAME__EVENTOBSERVABLE_HH

#include "Direction.hh"
class IObserver;

class IObservable {
public:
    virtual ~IObservable() = default;
    virtual void addObserver(IObserver *) = 0;
    virtual void removeObserver(IObserver *) = 0;
    virtual void notify(Direction) = 0;
};


#endif //STEP07_IOBSERVABLE_HH
