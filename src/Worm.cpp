
#include <iostream>
#include "Worm.hh"

Worm::Worm() {
    m_x = 0;
    m_y = 0;
    m_movement = sf::Vector2f(0.f, 0.f);
    m_speed = 50.f;
}

void Worm::move(Direction d) {
    if (d == RIGHT) {
        m_movement.x += m_speed;
    } else if (d == LEFT) {
        m_movement.x -= m_speed;
    }
}

void Worm::jump() {
    std::cout << "jump" << std::endl;

}

sf::Vector2f Worm::getMovement() const {
    return m_movement;
}

void Worm::resetMovement() {
    m_movement = sf::Vector2f(0.f, 0.f);
}
