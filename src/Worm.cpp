
#include <utility>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "Worm.hh"
#include "Constant.hh"


Worm::Worm(std::vector<Animation> animations) :
    Character(100,
            std::move(animations),
            AnimatedSprite(sf::seconds(0.1), true, true),
            sf::Vector2f(0.f, 0.f),
            100.f,
            300.f) {

    m_body->setOrigin(m_currentAnimation->getFrame(0).width / 2.f, m_currentAnimation->getFrame(0).height / 2.f);
    m_body->setPosition(Constant::SCREEN_DIMENSIONS / 2.f);
}

void Worm::update(sf::Time frameTime) {

    bool noKeyWasPressed = true;

//     m_velocity.x *= 0.5f;
    m_velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        Character::move(LEFT);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        Character::move(RIGHT);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_canJump) {
        Character::move(JUMP);
        noKeyWasPressed = false;
    }

    m_velocity.y += 981.f * frameTime.asSeconds();

    m_animatedSprite.play(*m_currentAnimation);
    m_body->move(m_velocity * frameTime.asSeconds());

    if (noKeyWasPressed && m_canJump) {
        m_animatedSprite.stop();
    }

    m_animatedSprite.update(frameTime);
}

sf::Vector2f Worm::getPosition() const {
    return m_body->getPosition();
}
