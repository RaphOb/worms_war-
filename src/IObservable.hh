//
// Created by geoff on 04/02/2020.
//

#ifndef STEP07_IOBSERVABLE_HH
#define STEP07_IOBSERVABLE_HH

class IObserver;

class IObservable {
public:
    virtual ~IObservable() = default;
    virtual void addObserver(IObserver *) = 0;
    virtual void removeObserver(IObserver *) = 0;
};


#endif //STEP07_IOBSERVABLE_HH
