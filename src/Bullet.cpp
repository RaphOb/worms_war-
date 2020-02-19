//
// Created by oraph on 19/02/2020.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Bullet.hh"

void Bullet::fireBullet(sf::Vector2f position) {
    body.setPosition((body.getPosition().x + 10), (body.getPosition().y -  10));
    body.setTexture(&texture);
    body.setScale(10,10);
}

Bullet::Bullet() {
    if (!texture.loadFromFile("../resources/bullet.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
        sprite.setTexture(texture);
    }
    std::cout <<" bullet construit" << std::endl;

}

Collider Bullet::getCollider() {
    return {body};
}

void Bullet::update(sf::Time frametime, sf::RenderWindow &window) {
//    body.setPosition((body.getPosition().x), (body.getPosition().y - 0.1f));
    std::cout << " bullet x : " << body.getPosition().x << std::endl;
    std::cout << " bullet y : " << body.getPosition().y << std::endl;
    window.draw(body);


}

Bullet::~Bullet() = default;
