
#include <utility>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <windef.h>
#include <winuser.h>
#include "Worm.hh"
#include "Constant.hh"
#include "Loader/ResourceLoader.hh"

Worm::Worm(std::vector<Animation> animations) :
        Character(100,
                  std::move(animations),
                  AnimatedSprite(sf::seconds(0.1), true, true),
                  sf::Vector2f(0.f, 0.f),
                  200.f,
                  300.f) {
    sprite.setTexture(ResourceLoader::getInstance().getTexture(BAZOOKA_TEXTURE));
    sprite.setTextureRect(sf::IntRect(52, 0, 52, 28));
    sprite.setOrigin(52.f / 2, 28.f / 2);

    m_body->setOrigin(m_currentAnimation->getFrame(0).width / 2.f, m_currentAnimation->getFrame(0).height / 2.f);
    m_body->setPosition(Constant::SCREEN_DIMENSIONS / 2.f);
}

void Worm::draw(sf::RenderWindow &window) {
    if (hasshot) {
        bullet->draw(window);
    }
    window.draw(sprite);
    window.draw(m_animatedSprite);
}

void Worm::move(Direction d) {
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
    HWND hwnd = GetActiveWindow();
//    std::cout << "orientation " << m_orientation << std::endl;
    sf::Vector2f b = sf::Vector2f(getPosition().x, getPosition().y);
    sf::Vector2f c = sf::Vector2f(getPosition().x - 5000, getPosition().y);
    GetCursorPos(&p);
    if (ScreenToClient(hwnd, &p)) {
        if (m_orientation == 0) {
            c = sf::Vector2f(m_body->getPosition().x + 5000, getPosition().y);
        }

        float numeroator = p.y * (b.x - c.x) + b.y * (c.x - p.x) + c.y * (p.x - b.x);
        float denominator = (p.x - b.x) * (b.x - c.x) + (p.y - b.y) * (b.y - c.y);
        float ratio = numeroator / denominator;
        float anglerad = atan(ratio);
        angle = ((anglerad * 180) / Constant::PI);
        if (angle > 90) {
            angle = 180 - angle;
        }
        if (angle < -90) {
            angle = 180 + angle;
        }
        if (angle >= -40.f && angle <= 45.f) {
            if (m_orientation == 1) {
                sprite.setRotation(angle + 12);
            } else {
                sprite.setRotation(angle - 12);

            }
        }
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
        bullet->fireBullet(sprite.getPosition(), angle);
        hasshot = true;
        noKeyWasPressed = false;
    }
    if (hasshot) {
        bullet->update();
    }
    // update pos bazooka
    sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 20, Worm::getPosition().y - 3));
    if (m_orientation == LEFT) {
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
