
#include <utility>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <windef.h>
#include <winuser.h>
#include <wingdi.h>
#include "Worm.hh"
#include "Constant.hh"
#include "Loader/ResourceLoader.hh"

float PI = 3.14159265359f;
Worm::Worm(std::vector<Animation> animations) :
    Character(100,
            std::move(animations),
            AnimatedSprite(sf::seconds(0.1), true, true),
            sf::Vector2f(0.f, 0.f),
            200.f,
            300.f) {
    sprite.setTexture(ResourceLoader::getInstance().getTexture(BAZOOKA_TEXTURE));
    sprite.setTextureRect(sf::IntRect(52, 0, 52, 28));
    sprite.setOrigin(52.f/2,28.f/2);

    m_body->setOrigin(m_currentAnimation->getFrame(0).width / 2.f, m_currentAnimation->getFrame(0).height / 2.f);
    m_body->setPosition(Constant::SCREEN_DIMENSIONS / 2.f);
}

void Worm::draw(sf::RenderWindow &window) {
    if (hasshot) {
//        window.draw(bullet);
        bullet->draw(window);
    }
    window.draw(sprite);
    window.draw(m_animatedSprite);
}

void Worm::move(Direction d) {
    //std::cout << "move "<< std::endl;
    if (d == RIGHT) {
        sprite.setTextureRect(sf::IntRect(0, 0, 52, 28));
        m_velocity.x += m_speed;
        if (m_canJump)
            m_currentAnimation = &m_animations[RIGHT];
        else
            m_currentAnimation = &m_animations[3];
        m_orientation = RIGHT;
    } else if (d == LEFT) {
        sprite.setTextureRect(sf::IntRect(52, 0, 52, 28));
        m_velocity.x -= m_speed;
        if (m_canJump)
            m_currentAnimation = &m_animations[LEFT];
        else
            m_currentAnimation = &m_animations[2];
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
    POINT p;
    sf::Vector2f b = sf::Vector2f(abs(getPosition().x - 1000),abs(getPosition().y));
    sf::Vector2f c = sf::Vector2f(getPosition().x + 1000,getPosition().y);
    if(GetCursorPos(&p)) {
        POINTFLOAT pb = {b.x - p.x, b.y - p.y};
        POINTFLOAT cb = {b.x - c.x, b.y - c.y};

//        float dot = (pb.x * cb.x + pb.y * cb.y);
//        float cross = (pb.x * cb.y - pb.y * cb.x);
//        float alpha = atan2(cross, dot);
//       float angle =  floor(alpha * 180. / PI);
//        std::cout << "angle is " << angle << std::endl;
        float angba = atan2(pb.y, pb.x);
        float angbc = atan2(cb.y, cb.x);
        float rslt = angbc - angba;
        float rs = (rslt * 180) / PI;
        std::cout << "angle is " << rs << std::endl;
        sprite.setRotation(rs);

    }

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
    sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 20, Worm::getPosition().y - 3));
    if(m_orientation == LEFT){
        sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 20, Worm::getPosition().y - 3));
    } else if (m_orientation == RIGHT) {
        sprite.setPosition(sf::Vector2f(Worm::getPosition().x + 20, Worm::getPosition().y - 3));
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
