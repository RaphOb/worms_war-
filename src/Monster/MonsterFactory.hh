//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_MONSTERFACTORY_HH
#define LITTLEBIGGAME_MONSTERFACTORY_HH

#include "../Character.hh"

class MonsterFactory {
public:
    Character* Create(const std::string&);
};

#endif //LITTLEBIGGAME_MONSTERFACTORY_HH
