//
// Created by oraph on 19/02/2020.
//

#include <cmath>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include "Bullet.hh"
#include "Direction.hh"
#include "Loader/ResourceLoader.hh"
#include "Constant.hh"


void Bullet::fireBullet(sf::Vector2f position, float angle) {
    if (angle > 45.f) {
        angle = 45.f;
    } else if (angle < -40.f) {
        angle = -40.f;
    }
    m_angle = (angle * Constant::PI / 180);
    if (m_orientation == RIGHT) {
        m_body->setTextureRect(sf::IntRect(0, 0, 11, 8));
    } else {
        m_body->setTextureRect(sf::IntRect(0, 8, 11, 8));
    }
    m_body->setPosition((position.x - 10), (position.y - 7));
    m_body->setRotation(angle);
    clock1.restart();
}

Bullet::Bullet(int orientation) : AbstractEntity() {
    m_body->setOrigin(5, 5);
    m_body->setTexture(&ResourceLoader::getInstance().getTexture(BULLET_TEXTURE));
    m_body->setSize(sf::Vector2f(20.f, 15.f));
    m_orientation = orientation;
}

Collider Bullet::getCollider() {
    return Collider(m_body);
}

void Bullet::update() {
    if (m_orientation == RIGHT) {
        m_body->setPosition((m_body->getPosition().x + std::cos(m_angle - 0.2617993878f) * 15.f),
                            (m_body->getPosition().y) + std::sin(m_angle - 0.2617993878f) * 20.f +
                            10.0f * clock1.getElapsedTime().asSeconds());
        m_body->setRotation(m_body->getRotation() + 1.5f);

    } else {
        m_body->setPosition((m_body->getPosition().x - (std::cos(m_angle + 0.2617993878f) * 15.f)),
                            (m_body->getPosition().y) + std::sin(-m_angle) * 20.f +
                            10.0f * clock1.getElapsedTime().asSeconds());
        m_body->setRotation(m_body->getRotation() - 1.5f);
    }
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(*m_body);
}

void Bullet::update(sf::Time frameTime) {

}

std::string Bullet::Serialize() {
    return std::__cxx11::string();
}

void Bullet::onCollision(sf::Vector2f direction) {
    delete (this);

}

sf::Vector2f Bullet::getposition() {
    return m_body->getPosition();
}

void Bullet::setPosition(sf::Vector2f pos) {
    m_body->setPosition(pos);

}

Bullet::~Bullet() = default;
