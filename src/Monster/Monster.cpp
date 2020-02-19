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

    m_velocity = sf::Vector2f(0.f, 0.f);
    m_speed = 100.f;
    m_jumpHeight = 300.f;
    m_canJump = true;
    m_animations = {walkingAnimationRight, walkingAnimationLeft};
    m_currentAnimation = &m_animations[LEFT];
    m_orientation = LEFT;


    animSprite.setOrigin((m_currentAnimation->getFrame(0).width / 2)+10, m_currentAnimation->getFrame(0).height / 2);
}