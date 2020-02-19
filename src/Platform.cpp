//
// Created by geoff on 13/02/2020.
//

#include "Platform.hh"

Platform::Platform(sf::Texture *texture, sf::Vector2f size, sf::Vector2f pos) {
    body.setSize(size);
    body.setPosition(pos);
    body.setTexture(texture);
    body.setOrigin(size / 2.0f);
}

void Platform::draw(sf::RenderWindow &window) {
    window.draw(body);
}

Collider Platform::getCollider() {
    return {body};
}
