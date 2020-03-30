//
// Created by oraph on 30/03/2020.
//

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "EventObservable.hh"

void EventObservable::addObserver(IObserver *o) {
    observers.emplace_back(o);

}

void EventObservable::removeObserver(IObserver *o) {
    observers.remove(o);
}

void EventObservable::notify(Direction e) {
    for (auto o : observers) {
        o->onNotify(e);
    }
}

void EventObservable::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        notify(LEFT);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        notify(RIGHT);
    } else {
            notify(NOTHING);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            notify(JUMP);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            notify(FIRE);
        }


    }
