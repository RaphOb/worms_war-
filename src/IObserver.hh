//
// Created by geoff on 04/02/2020.
//

#ifndef STEP07_IOBSERVER_HH
#define STEP07_IOBSERVER_HH

#include "IObservable.hh"

class IObservable;

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void Notify(IObservable *) = 0;
};


#endif //STEP07_IOBSERVER_HH
