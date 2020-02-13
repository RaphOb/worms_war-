//
// Created by geoff on 04/02/2020.
//

#ifndef STEP07_IOBSERVABLE_HH
#define STEP07_IOBSERVABLE_HH

#include "IObserver.hh"

class IObservable {
public:
    virtual ~IObservable() = default;
    virtual void AddObserver(IObserver *) = 0;
    virtual void RemoveObserver(IObserver *) = 0;
};


#endif //STEP07_IOBSERVABLE_HH
