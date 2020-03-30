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
    for(auto o : observers) {
        o->onNotify(e);
    }
}

void EventObservable::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
      notify(LEFT);
      std::cout <<"left"<<std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
       notify(RIGHT);
        std::cout <<"right"<<std::endl;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      notify(JUMP);
        std::cout <<"jump"<<std::endl;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
       notify(FIRE);
        std::cout <<"fire"<<std::endl;
    }

}
