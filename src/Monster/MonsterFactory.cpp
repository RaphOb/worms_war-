//
// Created by lafay on 18/02/2020.
//

#include <iostream>
#include "MonsterFactory.hh"
#include "../Character.hh"
#include "GroundMonster.hh"
#include "SkyMonster.hh"

using namespace std;

MonsterFactory::MonsterFactory() {
    initTextures();
}

bool MonsterFactory::initTextures() {
    if (!m_walkingTexture.loadFromFile("../resources/ground_monster.png")) {
        std::cout << "Failed to load monsters spritesheet!" << std::endl;
        return false;
    }

    if (!m_jumpingTexture.loadFromFile("../resources/ground_monster.png")) {
        std::cout << "Failed to load monster jumps" << std::endl;
        return false;
    }

    return true;
}

Monster* MonsterFactory::Create(const std::string &name, const sf::Vector2f& position) {
    if (name == "GroundMonster") {
        std::vector<sf::IntRect> leftMonster = {
                sf::IntRect(0, 29, 37, 25),
                sf::IntRect(37, 29, 37, 25),
                sf::IntRect(74, 29, 37, 25)
        };

        std::vector<sf::IntRect> rightMonster = {
                sf::IntRect(0, 54, 37, 25),
                sf::IntRect(37, 54, 37, 25),
                sf::IntRect(74, 54, 37, 25)
        };

        // TODO jump position
        std::vector<sf::IntRect> jumpLeftMonster = {
                sf::IntRect(0, 29, 44, 25),
                sf::IntRect(44, 29, 44, 25),
                sf::IntRect(88, 29, 44, 25)
        };

        std::vector<sf::IntRect> jumpRightMonster = {
                sf::IntRect(0, 54, 44, 25),
                sf::IntRect(44, 54, 44, 25),
                sf::IntRect(88, 54, 44, 25)
        };

        Animation walkingAnimationLeftMonster = Animation(leftMonster, m_walkingTexture);
        Animation walkingAnimationRightMonster = Animation(rightMonster, m_walkingTexture);
        Animation jumpingAnimationLeftMonster = Animation(jumpLeftMonster, m_jumpingTexture);
        Animation jumpingAnimationRightMonster = Animation(jumpRightMonster, m_jumpingTexture);

        return new GroundMonster({walkingAnimationRightMonster, walkingAnimationLeftMonster, jumpingAnimationLeftMonster, jumpingAnimationRightMonster}, position);
    } else if (name == "SkyMonster") {
        std::vector<sf::IntRect> leftMonster = {
                sf::IntRect(0, 29, 44, 25),
                sf::IntRect(44, 29, 44, 25),
                sf::IntRect(88, 29, 44, 25)
        };

        std::vector<sf::IntRect> rightMonster = {
                sf::IntRect(0, 54, 44, 25),
                sf::IntRect(44, 54, 44, 25),
                sf::IntRect(88, 54, 44, 25)
        };

        std::vector<sf::IntRect> jumpLeftMonster = {
                sf::IntRect(0, 29, 44, 25),
                sf::IntRect(44, 29, 44, 25),
                sf::IntRect(88, 29, 44, 25)
        };

        std::vector<sf::IntRect> jumpRightMonster = {
                sf::IntRect(0, 54, 44, 25),
                sf::IntRect(44, 54, 44, 25),
                sf::IntRect(88, 54, 44, 25)
        };

        Animation walkingAnimationLeftMonster = Animation(leftMonster, m_walkingTexture);
        Animation walkingAnimationRightMonster = Animation(rightMonster, m_walkingTexture);
        Animation jumpingAnimationLeftMonster = Animation(jumpLeftMonster, m_jumpingTexture);
        Animation jumpingAnimationRightMonster = Animation(jumpRightMonster, m_jumpingTexture);

        return new SkyMonster({walkingAnimationRightMonster, walkingAnimationLeftMonster, jumpingAnimationLeftMonster, jumpingAnimationRightMonster}, position);
    } else {
        return nullptr;
    }
}