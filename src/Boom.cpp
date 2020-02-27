//
// Created by oraph on 22/02/2020.
//

#include <iostream>
#include "Boom.hh"

void Boom::makeBoom(sf::Vector2f position) {

}

Boom::Boom(std::vector<Animation> animations, sf::Vector2f pos, AnimatedSprite animatedSprite) : m_animations(std::move(animations)),
        m_animatedSprite(std::move(animatedSprite)),
        AbstractEntity(&animatedSprite.getBody())
{
    m_currentAnimation = &m_animations[0];
//    m_body->setSize(sf::Vector2f(10.f,10.f));
    m_body->setPosition(pos);

}

void Boom::loopAnimmation(sf::RenderWindow &window,sf::Time frameTime) {
    int frame = 0;
    while (m_currentAnimation->getSize() !=frame) {
        draw(window);
        update(frameTime);
        frame++;
    }
}


void Boom::draw(sf::RenderWindow &window) {
    window.draw(*m_body);

}

void Boom::update(sf::Time frameTime) {
    m_body->setOrigin(m_currentAnimation->getFrame(0).width / 2.f, m_currentAnimation->getFrame(0).height / 1.12f);
    age += frameTime.asSeconds();
    if ( age < LIFE_TIME) {
    m_animatedSprite.play(*m_currentAnimation);
    m_animatedSprite.update(frameTime);
    } else {
        destroy = true;
    }
//    std::cout << "Current: "  << m_currentAnimation->getSize()<<std::endl;

}

void Boom::onCollision(sf::Vector2f direction) {

}

std::string Boom::Serialize() {
    return std::__cxx11::string();
}

void Boom::setPosition(float x, float y) {
    sf::Vector2f pos = sf::Vector2f(x, y);
    m_body->setPosition(pos);

}

Boom::Boom(const Boom &other, sf::Vector2f pos)  : m_animations(other.m_animations),m_animatedSprite(other.m_animatedSprite),AbstractEntity(other) {
    m_currentAnimation = &m_animations[0];
    std::cout << "COPY du BOOM"<< std::endl;

}
