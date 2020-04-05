#include <iostream>
#include <utility>
#include <cmath>
#include "Character.hh"
#include "Constant.hh"

int Character::getLife() const {
    return m_life;
}

void Character::setLife(int life) {
    this->m_life = life;
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(m_animatedSprite);
}


std::string Character::Serialize() {
    std::string str;
    str.append("m_life:").append(std::to_string(this->m_life)).append(";");
//    str.append("m_x:").append(std::to_string(this->m_x)).append(";");
//    str.append("m_y:").append(std::to_string(this->m_y));
    return str;
}

Character::Character(int l, std::vector<Animation> animations, AnimatedSprite animatedSprite, sf::Vector2f velocity,
                    float speed, float jumpHeight):
    AbstractEntity(&animatedSprite.getBody()),
    m_life(l),
    m_animations(std::move(animations)),
    m_currentAnimation(&m_animations[LEFT]),
    m_animatedSprite(std::move(animatedSprite)),
    m_velocity(velocity),
    m_speed(speed),
    m_canJump(true),
    m_jumpHeight(jumpHeight),
    m_orientation(LEFT)
    {

}

bool Character::canJump() const {
    return m_canJump;
}

void Character::onCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f) {
        // Collision on the left
        m_velocity.x = 0.0f;
    } else if (direction.x > 0.0f) {
        // Collision on the right
        m_velocity.x = 0.0f;
    } else if (direction.y < 0.0f) {
        // Collision on the bottom
        m_velocity.y = 0.0f;
        m_canJump = true;
        m_currentAnimation = &m_animations[m_orientation];
    } else if (direction.y > 0.0f) {
        // Collision on the top
        m_velocity.y = 0.0f;
    }
}

Collider Character::getCollider() {
    return {m_body};
}

void Character::move(Direction d) {
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
