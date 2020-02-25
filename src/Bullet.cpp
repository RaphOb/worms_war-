//
// Created by oraph on 19/02/2020.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <math.h>
#include "Bullet.hh"
#include "Direction.hh"
#include "Loader/ResourceLoader.hh"

void Bullet::fireBullet(sf::Vector2f position) {
    if (m_orientation == RIGHT) {
        m_body->setTextureRect(sf::IntRect(0, 0, 11, 8));
    } else {
        m_body->setTextureRect(sf::IntRect(0, 8, 11, 8));
    }
    std::cout << "pos x" << position.x << "pos y" << position.y << std::endl;
    m_body->setPosition((position.x - 10), (position.y - 7));
//    m_body->setScale(10,10);
    clock1.restart();
}

Bullet::Bullet(int orientation): AbstractEntity() {
    m_body->setOrigin(5, 5);
    m_body->setTexture(&ResourceLoader::getInstance().getTexture(BULLET_TEXTURE));
    m_body->setSize(sf::Vector2f(20.f, 15.f));
    m_orientation = orientation;
    std::cout << " bullet construit" << std::endl;

}

Collider Bullet::getCollider() {
    std::cout << " position body x" << m_body->getPosition().x<< " position y : "<< m_body->getPosition().y << std::endl;
    return Collider(m_body);
}

void Bullet::update() {
    if (m_orientation == RIGHT) {
        m_body->setPosition((m_body->getPosition().x + (speed/1.01f)),
                           (m_body->getPosition().y) + 1.0f * clock1.getElapsedTime().asSeconds());
        m_body->setRotation(m_body->getRotation() + 0.9f);

    } else {
        m_body->setPosition((m_body->getPosition().x - (speed/1.01f)),
                           (m_body->getPosition().y) + 1.0f * clock1.getElapsedTime().asSeconds());
        m_body->setRotation(m_body->getRotation() - 0.9f);
    }
    speed = speed/1.1f;
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
