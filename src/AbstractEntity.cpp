#include <iostream>
#include "AbstractEntity.hh"
#include "Constant.hh"

void AbstractEntity::draw(sf::RenderWindow &window) {
    window.draw(*m_body);
}

AbstractEntity::AbstractEntity() {
    m_body = new sf::RectangleShape();
}

AbstractEntity::AbstractEntity(sf::RectangleShape *body) {
    m_body = body;
}

void AbstractEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    std::cout << "DRAW" << std::endl;
    target.draw(*m_body, states);
}
