//
// Created by geoff on 04/02/2020.
//

#ifndef STEP07_IOBSERVER_HH
#define STEP07_IOBSERVER_HH

#include "IObservable.hh"
#include "Direction.hh"
//#include "observable/EventObservable.hh"

class IObservable;

enum class TypeEvent;

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify(Direction) = 0;
};


#endif //STEP07_IOBSERVER_HH
