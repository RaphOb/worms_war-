//
// Created by lafay on 18/02/2020.
//

#include "MonsterFactory.hh"
#include "../Character.hh"
#include "GroundMonster.hh"
#include "SkyMonster.hh"

using namespace std;

Character* MonsterFactory::Create(const std::string &name, AnimatedSprite animatedSprite, std::vector<Animation> animations) {
    if (name == "GroundMonster") {
        return new GroundMonster(animatedSprite, animations);
    } else if (name == "SkyMonster") {
        return new SkyMonster(animatedSprite, animations);
    } else {
        return nullptr;
    }
}