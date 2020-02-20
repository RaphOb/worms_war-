//
// Created by geoff on 19/02/2020.
//

#include <iostream>
#include "Game.hh"
#include "Animation.hh"
#include "AnimatedSprite.hh"

Game::Game() {
    shape = sf::RectangleShape();
    if (!initTextures())
        exit(-1);
    initWorm();
}

bool Game::initTextures() {
    if (!m_walkingTexture.loadFromFile("../resources/worms_character2.png")) {
        std::cout << "Failed to load worms spritesheet!" << std::endl;
        return false;
    }

    sf::Texture jumpingTexture;
    if (!m_jumpingTexture.loadFromFile("../resources/worms_jump.png")) {
        std::cout << "Failed to load worms jumps" << std::endl;
        return false;
    }

    return true;
}

Worm Game::initWorm() {
    std::vector<sf::IntRect> left = {
            sf::IntRect(0, 0, 32, 34),
            sf::IntRect(32, 0, 32, 34),
            sf::IntRect(64, 0, 32, 34)
    };

    std::vector<sf::IntRect> right = {
            sf::IntRect(0, 34, 32, 34),
            sf::IntRect(32, 34, 32, 34),
            sf::IntRect(64, 34, 32, 34)
    };

    std::vector<sf::IntRect> jumpLeft = {
            sf::IntRect(0, 0, 28, 52),
            sf::IntRect(28, 0, 28, 52),
            sf::IntRect(56, 0, 28, 52),
            sf::IntRect(84, 0, 28, 52)
    };

    std::vector<sf::IntRect> jumpRight = {
            sf::IntRect(0, 52, 28, 52),
            sf::IntRect(28, 52, 28, 52),
            sf::IntRect(56, 52, 28, 52),
            sf::IntRect(84, 52, 28, 52)
    };

    Animation walkingAnimationLeft = Animation(left, m_walkingTexture);
    Animation walkingAnimationRight = Animation(right, m_walkingTexture);
    Animation jumpingAnimationLeft = Animation(jumpLeft, m_jumpingTexture);
    Animation jumpingAnimationRight = Animation(jumpRight, m_jumpingTexture);

    AnimatedSprite animatedSprite(sf::seconds(0.1), true, true);

    Worm worm(animatedSprite,
              {walkingAnimationRight, walkingAnimationLeft, jumpingAnimationLeft, jumpingAnimationRight});
    return worm;
}
