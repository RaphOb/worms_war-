
#include <utility>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
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
    Worm::textureLoad();
    sprite.setTexture(bazookaTexture);
    sprite.setTextureRect(sf::IntRect(52, 0, 52, 28));

    m_body->setOrigin(m_currentAnimation->getFrame(0).width / 2.f, m_currentAnimation->getFrame(0).height / 2.f);
    m_body->setPosition(Constant::SCREEN_DIMENSIONS / 2.f);
}

void Worm::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(m_animatedSprite);
    if (hasshot) {
//        window.draw(bullet);
        bullet->draw(window);
    }
}

void Worm::move(Direction d) {
    std::cout << "move "<< std::endl;
    if (d == RIGHT) {
        sprite.setTextureRect(sf::IntRect(0, 0, 52, 28));
        m_velocity.x += m_speed;
        if (m_canJump)
            m_currentAnimation = &m_animations[RIGHT];
        m_orientation = RIGHT;
    } else if (d == LEFT) {
        sprite.setTextureRect(sf::IntRect(52, 0, 52, 28));
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

void Worm::update(sf::Time frameTime) {

    bool noKeyWasPressed = true;

//     m_velocity.x *= 0.5f;
    m_velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(LEFT);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(RIGHT);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_canJump) {
        move(JUMP);
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !hasshot) {
        bullet = new Bullet(m_orientation);
        bullet->fireBullet(getPosition());
        hasshot = true;
        noKeyWasPressed = false;
    }
    if(hasshot) {
        bullet->update();
    }
    // update pos bazooka
    sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 47, Worm::getPosition().y - 15));
    if(m_orientation == LEFT){
        sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 47, Worm::getPosition().y - 15));
    } else if (m_orientation == RIGHT) {
        sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 5, Worm::getPosition().y - 15));
    }
    // end update pos bazooka

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

Bullet &Worm::getBullet() const {
    return *bullet;
}
