//
// Created by geoff on 19/02/2020.
//

#include <iostream>
#include "Game.hh"
#include "Animation.hh"
#include "AnimatedSprite.hh"
#include "Loader/ResourceLoader.hh"

Game::Game() {
    initWorm();
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

    Animation walkingAnimationLeft = Animation(left, ResourceLoader::getInstance().getTexture(WORM_WALKING_TEXTURE));
    Animation walkingAnimationRight = Animation(right, ResourceLoader::getInstance().getTexture(WORM_WALKING_TEXTURE));
    Animation jumpingAnimationLeft = Animation(jumpLeft, ResourceLoader::getInstance().getTexture(WORM_JUMPING_TEXTURE));
    Animation jumpingAnimationRight = Animation(jumpRight, ResourceLoader::getInstance().getTexture(WORM_JUMPING_TEXTURE));


    return Worm({walkingAnimationRight, walkingAnimationLeft, jumpingAnimationLeft, jumpingAnimationRight});
}
