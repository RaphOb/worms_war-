//
// Created by oraph on 22/02/2020.
//

#include <iostream>
#include "Boom.hh"

void Boom::makeBoom(sf::Vector2f position) {

}

Boom::Boom(std::vector<Animation> animations, sf::Vector2f pos) : Character(0, std::move(animations),
                         AnimatedSprite(sf::seconds(0.1), true, true),
                         sf::Vector2f(0.f, 0.f),
                         0.f,
                         0.f) {
    m_body->setSize(sf::Vector2f(360.f,220.f));
    m_body->setPosition(pos);
    m_body->setOrigin(m_body->getSize().x/2,m_body->getSize().y/2);
    std::cout << "construction du BOOM"<< std::endl;

}

void Boom::draw(sf::RenderWindow &window) {
    window.draw(m_animatedSprite);
    std::cout << "dans le draw"  << std::endl;
}

void Boom::update(sf::Time frameTime) {
    std::cout << "dans le update et la pos est : "  << m_body->getPosition().x<<std::endl;
    m_currentAnimation = &m_animations[0];
    m_animatedSprite.play(*m_currentAnimation);
    m_animatedSprite.update(frameTime);

}
