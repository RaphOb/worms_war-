//
// Created by oraph on 19/02/2020.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Bullet.hh"

void Bullet::fireBullet(sf::Vector2f position) {
    body.setPosition(position);
    body.setTexture(&texture);
}

Bullet::Bullet() {
    if (!texture.loadFromFile("../resources/bullet.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
        sprite.setTexture(texture);
    }

}

Collider Bullet::getCollider() {
    return {body};
}

void Bullet::update(sf::Time frametime, sf::RenderWindow &window) {
    body.setPosition((body.getPosition().x * frametime.asSeconds()), -(body.getPosition().y * 2.0f * 981.f));
    window.draw(body);


}

Bullet::~Bullet() = default;
