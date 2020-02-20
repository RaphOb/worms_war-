//
// Created by lafay on 18/02/2020.
//

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Monster.hh"
#include "../Animation.hh"
#include "../AnimatedSprite.hh"
#include "../Constant.cpp"

using namespace std;

Monster::Monster(AnimatedSprite animatedSprite, std::vector<Animation> animations) : m_animatedSprite(animatedSprite){
    m_velocity = sf::Vector2f(0.f, 0.f);
    m_speed = 100.f;
    m_jumpHeight = 300.f;
    m_canJump = true;
    m_animations = std::move(animations);
    m_currentAnimation = &m_animations[Constant::LEFT];
    m_orientation = Constant::LEFT;
    m_animatedSprite.setOrigin(m_currentAnimation->getFrame(0).width / 2, m_currentAnimation->getFrame(0).height / 2);
}

void Monster::onCollision(sf::Vector2f direction) {
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

Collider Monster::getCollider() {
    body = &m_animatedSprite.getBody();
    return Collider(*body);
}

sf::Vector2f Monster::getPosition() const {
    return m_animatedSprite.getBody().getPosition();
}

void Monster::update(sf::Time frameTime) {

    bool noKeyWasPressed = true;

//     m_velocity.x *= 0.5f;
    m_velocity.x = 0.0f;

    m_velocity.y += 981.f * frameTime.asSeconds();

    m_animatedSprite.play(*m_currentAnimation);
    m_animatedSprite.getBody().move(m_velocity * frameTime.asSeconds());

    if (noKeyWasPressed && m_canJump) {
        m_animatedSprite.stop();
    }

    m_animatedSprite.update(frameTime);
}

void Monster::draw(sf::RenderWindow& window) {
    window.draw(m_animatedSprite);
}
/*
Monster::Monster() {
    sf::Texture walkingTexture;
    if (!walkingTexture.loadFromFile("../resources/ground_monster.png")) {
        std::cout << "Failed to load ground monster spritesheet!" << std::endl;
    }

    std::vector<sf::IntRect> left = {
            sf::IntRect(432, 240, 48, 48),
            sf::IntRect(480, 240, 48, 48),
            sf::IntRect(528, 240, 48, 48)
    };

    std::vector<sf::IntRect> right = {
            sf::IntRect(432, 288, 48, 48),
            sf::IntRect(480, 288, 48, 48),
            sf::IntRect(528, 288, 48, 48)
    };

    Animation walkingAnimationLeft = Animation(left, walkingTexture);
    Animation walkingAnimationRight = Animation(right, walkingTexture);

    sf::Vector2i screenDimensions(Constant::VIEW_WIDTH, Constant::VIEW_HEIGHT);

    // set up AnimatedSprite
    sf::RectangleShape shape;
    AnimatedSprite animSprite(shape, sf::seconds(0.1), true, true);
    animSprite.getBody().setPosition(sf::Vector2f(screenDimensions / 2));

//    m_animatedSprite.getBody().setScale(3.0f, 3.0f);
    std::cout << animSprite.getBody().getPosition().x << animSprite.getBody().getPosition().y << std::endl;

}*/