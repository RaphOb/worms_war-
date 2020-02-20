//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_MONSTERFACTORY_HH
#define LITTLEBIGGAME_MONSTERFACTORY_HH

#include "../Character.hh"
#include "../AnimatedSprite.hh"

class MonsterFactory {
public:
    Character* Create(const std::string&, AnimatedSprite, std::vector<Animation>);
};

#endif //LITTLEBIGGAME_MONSTERFACTORY_HH
