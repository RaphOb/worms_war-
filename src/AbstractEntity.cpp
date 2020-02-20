#include "AbstractEntity.hh"
#include "Constant.hh"

void AbstractEntity::draw(sf::RenderWindow &window) {}

AbstractEntity::AbstractEntity(sf::RectangleShape &body) {
    this->m_body = &body;
}

void AbstractEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*m_body, states);
}
