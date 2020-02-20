//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_SKYMONSTER_HH
#define LITTLEBIGGAME_SKYMONSTER_HH

#include "Monster.hh"

using namespace std;

class SkyMonster : public Monster {
public:
    SkyMonster(AnimatedSprite, std::vector<Animation>);
};

#endif //LITTLEBIGGAME_SKYMONSTER_HH
