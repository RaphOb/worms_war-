//
// Created by lafay on 18/02/2020.
//

#include <iostream>
#include "MonsterFactory.hh"
#include "../Character.hh"
#include "GroundMonster.hh"
#include "SkyMonster.hh"
#include "../Loader/ResourceLoader.hh"

using namespace std;

MonsterFactory::MonsterFactory() {
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

        Animation walkingAnimationLeftMonster = Animation(leftMonster, ResourceLoader::getInstance().getTexture(MONSTER_WALKING_TEXTURE));
        Animation walkingAnimationRightMonster = Animation(rightMonster, ResourceLoader::getInstance().getTexture(MONSTER_WALKING_TEXTURE));
        Animation jumpingAnimationLeftMonster = Animation(jumpLeftMonster, ResourceLoader::getInstance().getTexture(MONSTER_WALKING_TEXTURE));
        Animation jumpingAnimationRightMonster = Animation(jumpRightMonster, ResourceLoader::getInstance().getTexture(MONSTER_WALKING_TEXTURE));

        return new GroundMonster({walkingAnimationRightMonster, walkingAnimationLeftMonster, jumpingAnimationLeftMonster, jumpingAnimationRightMonster}, position, m_pathfinding);
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

        Animation walkingAnimationLeftMonster = Animation(leftMonster, ResourceLoader::getInstance().getTexture(MONSTER_WALKING_TEXTURE));
        Animation walkingAnimationRightMonster = Animation(rightMonster, ResourceLoader::getInstance().getTexture(MONSTER_WALKING_TEXTURE));
        Animation jumpingAnimationLeftMonster = Animation(jumpLeftMonster, ResourceLoader::getInstance().getTexture(MONSTER_WALKING_TEXTURE));
        Animation jumpingAnimationRightMonster = Animation(jumpRightMonster, ResourceLoader::getInstance().getTexture(MONSTER_WALKING_TEXTURE));

        return new SkyMonster({walkingAnimationRightMonster, walkingAnimationLeftMonster, jumpingAnimationLeftMonster, jumpingAnimationRightMonster}, position, m_pathfinding);
    } else {
        return nullptr;
    }
}

void MonsterFactory::setPathfinding(Pathfinding *pathfinding) {
    m_pathfinding = pathfinding;
}

Pathfinding *MonsterFactory::getPathfinding() {
    return m_pathfinding;
}
