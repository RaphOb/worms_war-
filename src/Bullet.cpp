//
// Created by oraph on 19/02/2020.
//

#include <iostream>
#include "Bullet.hh"

void Bullet::fireBullet(sf::Vector2f position) {

}

Bullet::Bullet() {
    if (!texture.loadFromFile("../resources/bullet.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
    }

}

Collider Bullet::getCollider()  {
    return {body};
}

Bullet::~Bullet() = default;
