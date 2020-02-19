
#include <utility>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Worm.hh"


Worm::Worm(AnimatedSprite animatedSprite, std::vector<Animation> animations) : m_animatedSprite(animatedSprite) {
    m_velocity = sf::Vector2f(0.f, 0.f);
    m_speed = 100.f;
    m_jumpHeight = 300.f;
    m_canJump = true;
    m_animations = std::move(animations);
    m_currentAnimation = &m_animations[LEFT];
    m_orientation = LEFT;
    m_animatedSprite.setOrigin(m_currentAnimation->getFrame(0).width / 2, m_currentAnimation->getFrame(0).height / 2);
    Worm::textureLoad();
    sprite.setTexture(bazookaTexture);
}

sf::Vector2f Worm::getVelocity() const {
    return m_velocity;
}

bool Worm::canJump() const {
    return m_canJump;
}

void Worm::setYVelocity(float v) {
    m_velocity.y = v;
}

void Worm::draw(sf::RenderWindow &window) {
    sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 45, Worm::getPosition().y - 15));
    if(leftorright == 0){
    sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 45, Worm::getPosition().y - 15));
    } else if (leftorright == 1) {
        sprite.setPosition(sf::Vector2f(Worm::getPosition().x - 10, Worm::getPosition().y - 15));
    }
    window.draw(sprite);
    window.draw(m_animatedSprite);
}

void Worm::move(Direction d) {
    if (d == RIGHT) {
        leftorright = 1;
        sprite.setTextureRect(sf::IntRect(54, 0, 55, 34));
        m_velocity.x += m_speed;
        if (m_canJump)
            m_currentAnimation = &m_animations[RIGHT];
        m_orientation = RIGHT;
    } else if (d == LEFT) {
        leftorright = 0;
        sprite.setTextureRect(sf::IntRect(0, 0, 55, 34));
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

void Worm::update(sf::Time frameTime, sf::RenderWindow& window) {

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        bullet = std::make_unique<Bullet>();
        bullet->fireBullet(getPosition());
        hasshot = true;
        noKeyWasPressed = false;
        std::cout << "PUSH SUR A !"<< std::endl;
    }
    if(hasshot) {
    bullet->update(frameTime, window);
    }

    m_velocity.y += 981.f * frameTime.asSeconds();

    m_animatedSprite.play(*m_currentAnimation);
    m_animatedSprite.getBody().move(m_velocity * frameTime.asSeconds());

    if (noKeyWasPressed && m_canJump) {
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
        m_currentAnimation = &m_animations[m_orientation];
    } else if (direction.y > 0.0f) {
        // Collision on the top
        m_velocity.y = 0.0f;
    }
}

Collider Worm::getCollider() {
    body = &m_animatedSprite.getBody();
    return Collider(*body);
}
