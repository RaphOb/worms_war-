//
// Created by lafay on 18/02/2020.
//

#include "MonsterFactory.hh"
#include "../Character.hh"
#include "GroundMonster.hh"
#include "SkyMonster.hh"

using namespace std;

Character* MonsterFactory::Create(const std::string &name) {
    if (name == "GroundMonster") {
        return new GroundMonster();
    } else if (name == "SkyMonster") {
        return new SkyMonster();
    } else {
        return nullptr;
    }
}