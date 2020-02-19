//
// Created by oraph on 19/02/2020.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Bullet.hh"

void Bullet::fireBullet(sf::Vector2f position) {
    sprite.setTexture(texture);

    sprite.setPosition((position.x + 50), (position.y-  10));
    sprite.setScale(10,10);
}

Bullet::Bullet() {
    if (!texture.loadFromFile("../resources/bullet.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
//        body.setTexture(&texture);
    }
    std::cout <<" bullet construit" << std::endl;

}

Collider Bullet::getCollider() {
    return {body};
}

void Bullet::update(sf::Time frametime, sf::RenderWindow &window) {
    sprite.setPosition((sprite.getPosition().x + 0.00001f), (sprite.getPosition().y - 0.0001f));
    std::cout << " bullet x : " << sprite.getPosition().x << std::endl;
    std::cout << " bullet y : " << sprite.getPosition().y << std::endl;
    window.draw(sprite);


}

Bullet::~Bullet() = default;
