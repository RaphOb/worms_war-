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

    sf::Texture jumpingTexture;
    if (!m_jumpingTexture.loadFromFile("../resources/ground_monster.png")) {
        std::cout << "Failed to load monster jumps" << std::endl;
        return false;
    }

    return true;
}

Character* MonsterFactory::Create(const std::string &name) {
    if (name == "GroundMonster") {
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

        return new GroundMonster({walkingAnimationRightMonster, walkingAnimationLeftMonster, jumpingAnimationLeftMonster, jumpingAnimationRightMonster});
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

        return new SkyMonster({walkingAnimationRightMonster, walkingAnimationLeftMonster, jumpingAnimationLeftMonster, jumpingAnimationRightMonster});
    } else {
        return nullptr;
    }
}