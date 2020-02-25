//
// Created by oraph on 25/02/2020.
//

#include "Scenes.hh"

void Scenes::add(std::unique_ptr<AbstractEntity> element) {
    elements.push_back(std::move(element));

}

void Scenes::update(sf::Time myt) {
     //fix a bug that when you shake the window you fall through the floor because the game is paused but not frameTime. So you move by a lot in one frame.
//    if (myt.asSeconds() > 1.0f / 60.0f) {
//        myt = sf::seconds(1.0f / 60.0f);
//    }
    for (auto &e : elements) {
        e->update(myt);
    }

}

void Scenes::collide() {
    for (auto i{0u}; i < elements.size(); ++i) {
        for (auto j{0u}; j < elements.size(); ++j) {
            if (i != j) {
                //TODO gegtCollider dans l'abstract
            }
        }
    }

}

void Scenes::draw(sf::RenderWindow &window) {
    for (auto &e : elements) {
        e->draw(window);
    }

}

void Scenes::clean() {
    auto finTableau = std::remove_if(std::begin(elements), std::end(elements),
                                     [](auto &element) { return element->isDestroy(); });
    elements.erase(finTableau, std::end(elements));
}

void Scenes::clear() {

}

Scenes::Scenes() {

}

