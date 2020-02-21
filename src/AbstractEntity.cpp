#include <iostream>
#include "AbstractEntity.hh"
#include "Constant.hh"

void AbstractEntity::draw(sf::RenderWindow &window) {
//    std::cout << "window draw: " << m_body->getPosition().x << ", " << m_body->getPosition().y << std::endl;
    window.draw(*m_body);
}

AbstractEntity::AbstractEntity() {
    m_body = new sf::RectangleShape();
}

AbstractEntity::AbstractEntity(sf::RectangleShape *body) {
//    std::cout << "constru abstract: " << body->getPosition().x << ", " << body->getPosition().y << std::endl;
    m_body = body;
//    std::cout << "constru abstract: " << m_body->getPosition().x << ", " << m_body->getPosition().y << std::endl;
}

void AbstractEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    std::cout << "DRAW" << std::endl;
    target.draw(*m_body, states);
}
