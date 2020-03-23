//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_SKYMONSTER_HH
#define LITTLEBIGGAME_SKYMONSTER_HH

#include "Monster.hh"

using namespace std;

class SkyMonster : public Monster {
public:
    SkyMonster(std::vector<Animation>, const sf::Vector2f&, Pathfinding*);
};

#endif //LITTLEBIGGAME_SKYMONSTER_HH
