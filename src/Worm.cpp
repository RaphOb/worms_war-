
#include <utility>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <windef.h>
#include <winuser.h>
#include <SFML/Window/Event.hpp>
#include "Worm.hh"
#include "Constant.hh"
#include "Loader/ResourceLoader.hh"
#include "Audio/AudioManager.hh"
#include "observable/EventObservable.hh"

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
        if (m_canJump) {
            distance_covered += m_speed;
            m_currentAnimation = &m_animations[RIGHT];
        } else
            m_currentAnimation = &m_animations[3];
        m_orientation = RIGHT;
    } else if (d == LEFT) {
        sprite.setTextureRect(sf::IntRect(52, 0, 52, 28));
        m_velocity.x -= m_speed;
        if (m_canJump) {
            distance_covered += m_speed;
            m_currentAnimation = &m_animations[LEFT];
        } else
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
    if (m_orientation == LEFT) {
        sprite.setTextureRect(sf::IntRect(52, 0, 52, 28));
        sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 20, Worm::getPosition().y - 3));
    } else if (m_orientation == RIGHT) {
        sprite.setPosition(sf::Vector2f(Worm::getPosition().x + 20, Worm::getPosition().y - 3));
        sprite.setTextureRect(sf::IntRect(0, 0, 52, 28));
    }
    POINT p; // cursor
    HWND hwnd = GetActiveWindow(); // windows listener
    sf::Vector2f b = sf::Vector2f(getPosition().x, getPosition().y); //worms
    sf::Vector2f c = sf::Vector2f(getPosition().x - 5000, getPosition().y);
    GetCursorPos(&p);
    if (ScreenToClient(hwnd, &p)) {
        if (m_orientation == 0) {
            c = sf::Vector2f(m_body->getPosition().x + 5000, getPosition().y);
        }

        if (p.x > b.x) {
            m_orientation = RIGHT;
        }
        if (p.x < b.x) {
            m_orientation = LEFT;
        }

        float numeroator = p.y * (b.x - c.x) + b.y * (c.x - p.x) + c.y * (p.x - b.x);
        float denominator = (p.x - b.x) * (b.x - c.x) + (p.y - b.y) * (b.y - c.y);
        float ratio = numeroator / denominator;
        float anglerad = atan(ratio);
        angle = ((anglerad * 180) / Constant::PI);

        if (angle >= -40.f && angle <= 45.f) {
            if (m_orientation == 1) {
                sprite.setRotation(angle + 12);
            } else {
                sprite.setRotation(angle - 12);

            }
        }
    }


    m_velocity.x *= 0.6f;
    if (hasshot) {
        bullet->update();
    }

    if (distance_covered > 4000.f) {
        AudioManager::getInstance().addSound(WORM_WALKING_BUFFER);
        distance_covered = 0;
    }

    m_velocity.y += 981.f * frameTime.asSeconds();

    m_animatedSprite.play(*m_currentAnimation);
    m_body->move(m_velocity * frameTime.asSeconds());

    if (m_noKeyWasPressed && m_canJump) {
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

void Worm::onNotify(Direction e) {
    switch (e) {
        case LEFT:
            move(LEFT);
            m_noKeyWasPressed = false;
            break;
        case RIGHT:
            move(RIGHT);
            m_noKeyWasPressed = false;
            break;
        case JUMP:
            if (m_canJump) {
                move(JUMP);
                m_noKeyWasPressed = false;
            }
            break;
        case FIRE:
            if (!hasshot) {
                if (bulletTime.getElapsedTime().asSeconds() > 0.5) {
                    bullet = new Bullet(m_orientation);
                    bullet->fireBullet(sprite.getPosition(), angle);
                    hasshot = true;
                    m_noKeyWasPressed = false;
                    bulletTime.restart();
                    break;
                }
            }
        case NOTHING:
            m_noKeyWasPressed = true;
            break;
    }


}

void Worm::reduceLife() {
    this->m_life -= 10;
}
