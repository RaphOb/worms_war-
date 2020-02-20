//
// Created by oraph on 19/02/2020.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <math.h>
#include "Bullet.hh"

void Bullet::fireBullet(sf::Vector2f position, int leftorright) {
    sprite.setTexture(texture);
    clock1.restart();
    if (leftorright == 1) {
        sprite.setTextureRect(sf::IntRect(0, 0, 20, 15));
    } else {
        sprite.setTextureRect(sf::IntRect(0, 15, 20 , 15));

    }
    std::cout << position.x << position.y << std::endl;
    sprite.setPosition((position.x - 10), (position.y-10));
//    sprite.setScale(10,10);
}

Bullet::Bullet() {
    if (!texture.loadFromFile("../resources/bullet.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
//        body.setTexture(&texture);
    }
    std::cout << " bullet construit" << std::endl;

}

Collider Bullet::getCollider()  {
    return {&body};
}

void Bullet::update(int leftorright) {
    if (leftorright) {
    sprite.setPosition((sprite.getPosition().x + 0.410f/clock1.getElapsedTime().asSeconds()), (sprite.getPosition().y) + 1.0f* clock1.getElapsedTime().asSeconds());
    sprite.setRotation(sprite.getRotation()+0.9f);
//    sprite.setPosition((sprite.getPosition().x + 98.1f* clock1.getElapsedTime().asSeconds()), (sqrtf(2*9.81f*sprite.getPosition().y)));

    } else  {
        sprite.setPosition((sprite.getPosition().x - 10.f), (sprite.getPosition().y));

    }
    std::cout << " vitesse : " << clock1.getElapsedTime().asSeconds() << std::endl;
    std::cout << " bullet x : " << sprite.getPosition().x << std::endl;
//clock1.restart();
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

Bullet::~Bullet() = default;
