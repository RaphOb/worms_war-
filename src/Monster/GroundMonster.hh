//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_GROUNDMONSTER_HH
#define LITTLEBIGGAME_GROUNDMONSTER_HH

#include "Monster.hh"

using namespace std;

class GroundMonster : public Monster {
public:
    GroundMonster(std::vector<Animation>, const sf::Vector2f&);
};

#endif //LITTLEBIGGAME_GROUNDMONSTER_HH
