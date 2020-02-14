
#include <iostream>
#include <utility>
#include <math.h>
#include <SFML/Window/Keyboard.hpp>
#include "Worm.hh"

//Worm::Worm() : Character(100) {
//    m_velocity = sf::Vector2f(0.f, 0.f);
//    m_speed = 50.f;
//    m_jumpHeight = 50.f;
//    m_canJump = true;
//}

Worm::Worm(AnimatedSprite animatedSprite, std::vector<Animation> animations) : m_animatedSprite(animatedSprite){
    m_velocity = sf::Vector2f(0.f, 0.f);
    m_speed = 50.f;
    m_jumpHeight = 300.f;
    m_canJump = true;
//    m_animatedSprite = std::move(animatedSprite);
    m_animations = std::move(animations);
    m_currentAnimation = &m_animations[LEFT];

//    std::cout << m_animatedSprite.getLocalBounds().width << m_animatedSprite.getLocalBounds().height << std::endl;
    m_animatedSprite.setOrigin(m_currentAnimation->getFrame(0).width / 2, m_currentAnimation->getFrame(0).height / 2);
}

sf::Vector2f Worm::getVelocity() const {
    return m_velocity;
}

void Worm::resetVelocity() {
    // you can do m_velocity.m_x *= 0.5f to decrease it slowly and add a effect of inertia
    m_velocity = sf::Vector2f(0.f, 0.f);
}

bool Worm::canJump() const {
    return m_canJump;
}

void Worm::setYVelocity(float v){
    m_velocity.y = v;
}

void Worm::draw(sf::RenderWindow& window) {
//    Character::draw(window);
    window.draw(m_animatedSprite);
}

void Worm::move(Direction d) {
    if (d == RIGHT) {
        m_velocity.x += m_speed;
        if (m_canJump)
            m_currentAnimation = &m_animations[RIGHT];
        m_orientation = 2;
    } else if (d == LEFT) {
        m_velocity.x -= m_speed;
        if (m_canJump)
            m_currentAnimation = &m_animations[LEFT];
        m_orientation = 1;
    } else if (d == JUMP) {
        m_canJump = false;
        m_velocity.y = -sqrtf(2.0f * 981.f * m_jumpHeight);
        if (m_orientation == 1) {
            m_currentAnimation = &m_animations[2];
        } else if (m_orientation == 2) {
            m_currentAnimation = &m_animations[3];
        }
    }
}

void Worm::update(sf::Time frameTime) {

    bool noKeyWasPressed = true;
    sf::Vector2f direction;

    // m_velocity.x *= 0.5f;
    m_velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(LEFT);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(RIGHT);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_velocity.y -= m_speed;
        noKeyWasPressed = false;
//        m_currentAnimation = &m_animations[LEFT];
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_velocity.y += m_speed;
        noKeyWasPressed = false;
//        m_currentAnimation = &m_animations[RIGHT];
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_canJump) {
        move(JUMP);
        noKeyWasPressed = false;
    }

    m_velocity.y += 981.f * frameTime.asSeconds();


    m_animatedSprite.play(*m_currentAnimation);
    m_animatedSprite.getBody().move(m_velocity * frameTime.asSeconds());

//    std::cout << m_animatedSprite.getPosition().x << ", " << m_animatedSprite.getPosition().y << std::endl;
//    if (m_animatedSprite.getBody().getPosition().y > 200) {
//        std::cout << "oops" << std::endl;
//        direction.y = -1.0f;
//    }
//
//    onCollision(direction);
//    getCollider();

    if (noKeyWasPressed) {
        m_animatedSprite.stop();
    }

    m_animatedSprite.update(frameTime);


}

sf::Vector2f Worm::getPosition() const {
    return m_animatedSprite.getBody().getPosition();
}

void Worm::onCollision(sf::Vector2f direction) {
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
    } else if (direction.y > 0.0f) {
        // Collision on the top
        m_velocity.y = 0.0f;
    }
}

Collider Worm::getCollider() {
//    sf::RectangleShape shape({m_animatedSprite.getGlobalBounds().width, m_animatedSprite.getGlobalBounds().height});
//    shape.setPosition(m_animatedSprite.getPosition());
//
//    std::cout << "global bounds: ";
//    std::cout << m_animatedSprite.getGlobalBounds().width << ", " << m_animatedSprite.getGlobalBounds().height << std::endl;
    body = &m_animatedSprite.getBody();
    return Collider(*body);
}
