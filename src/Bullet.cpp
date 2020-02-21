//
// Created by oraph on 19/02/2020.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <math.h>
#include "Bullet.hh"

void Bullet::fireBullet(sf::Vector2f position, int leftorright) {
    std::cout << "bidule" << std::endl;
    m_body->setTexture(&texture);
    std::cout << "bidule" << std::endl;
    if (leftorright == 1) {
        m_body->setTextureRect(sf::IntRect(0, 0, 20, 15));
    } else {
        m_body->setTextureRect(sf::IntRect(0, 15, 20, 15));

    }
    std::cout << "pos x" << position.x << "pos y" << position.y << std::endl;
    m_body->setPosition((position.x - 10), (position.y - 10));
//    m_body->setScale(10,10);
    clock1.restart();
}

Bullet::Bullet(): AbstractEntity() {
//    body->setSize(sf::Vector2f(10.f,10.f));

    if (!texture.loadFromFile("../resources/bullet.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
//        body.setTexture(&texture);
    }
//    m_body = new sf::RectangleShape();
//    m_body->setPosition((position.x - 10), (position.y-10));
    m_body->setOrigin(5, 5);
    m_body->setTexture(nullptr);
    m_body->setSize(sf::Vector2f(20.f, 15.f));
    std::cout << " bullet construit" << std::endl;

}

Collider Bullet::getCollider() {
    std::cout << " position body x" << m_body->getPosition().x<< " position y : "<< m_body->getPosition().y << std::endl;
    return Collider(m_body);
}

void Bullet::update(int leftorright) {
    if (leftorright) {
        m_body->setPosition((m_body->getPosition().x + (1.10f)),
                           (m_body->getPosition().y) + 1.0f * clock1.getElapsedTime().asSeconds());
        m_body->setRotation(m_body->getRotation() + 0.9f);

    } else {
        m_body->setPosition((m_body->getPosition().x - (1.10f )),
                           (m_body->getPosition().y) + 1.0f * clock1.getElapsedTime().asSeconds());
        m_body->setRotation(m_body->getRotation() - 0.9f);
    }
    std::cout << " vitesse : " << clock1.getElapsedTime().asSeconds() << std::endl;
    std::cout << " position body x DANS UPDATE" << m_body->getPosition().x<< " position y : "<< m_body->getPosition().y << std::endl;

//    std::cout << " bullet x : " << m_body->getPosition().x << std::endl;
//clock1.restart();
}

void Bullet::draw(sf::RenderWindow &window){
//    std::cout << " position x dans le draw "  <<  m_body->getPosition().x <<std::endl;
//    std::cout << " size x dans le draw "  <<  m_body->getTexture()->getSize().x <<std::endl;
    window.draw(*m_body);
//    AbstractEntity::draw(window);



}

void Bullet::update(sf::Time frameTime) {

}

std::string Bullet::Serialize() {
    return std::__cxx11::string();
}

void Bullet::onCollision(sf::Vector2f direction) {
    delete(this);

}

Bullet::~Bullet() = default;
