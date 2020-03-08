//
// Created by lafay on 18/02/2020.
//

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Monster.hh"
#include "../Animation.hh"
#include "../AnimatedSprite.hh"
#include "../Character.hh"
#include "../Constant.hh"

using namespace std;

Monster::Monster(std::vector<Animation> animations, const sf::Vector2f& position) :
    Character(100,
              std::move(animations),
              AnimatedSprite(sf::seconds(0.1), true, true),
              sf::Vector2f(0.f, 0.f),
              100.f,
              300.f) {

        m_body->setOrigin(m_currentAnimation->getFrame(0).width / 2.f, m_currentAnimation->getFrame(0).height / 2.f);
        m_body->setPosition(position);
}


void Monster::draw(sf::RenderWindow &window) {
    window.draw(m_animatedSprite);
}

void Monster::move(Direction d) {
    if (d == RIGHT) {
        m_velocity.x += m_speed;
        if (m_canJump)
            m_currentAnimation = &m_animations[RIGHT];
        m_orientation = RIGHT;
    } else if (d == LEFT) {
        m_velocity.x -= m_speed;
        if (m_canJump)
            m_currentAnimation = &m_animations[LEFT];
        m_orientation = LEFT;
    } else if (d == JUMP) {
        m_canJump = false;
        m_velocity.y = -sqrtf(2.0f * 981.f * m_jumpHeight);
        if (m_orientation == LEFT) {
            m_currentAnimation = &m_animations[2];
        } else if (m_orientation == RIGHT) {
            m_currentAnimation = &m_animations[3];
        }
    }
}

void Monster::update(sf::Time frameTime) {

    bool noKeyWasPressed = true;

//     m_velocity.x *= 0.5f;
    m_velocity.x = 0.0f;

    move(LEFT);

    m_velocity.y += 981.f * frameTime.asSeconds();

    m_animatedSprite.play(*m_currentAnimation);
    m_body->move(m_velocity * frameTime.asSeconds());

    m_animatedSprite.update(frameTime);
}

sf::Vector2f Monster::getPosition() const {
    return m_body->getPosition();
}

Pathfinding *Monster::getPathfinding() {
    return m_pathfinding;
}
