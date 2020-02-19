//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_MONSTER_HH
#define LITTLEBIGGAME_MONSTER_HH

#include "../Animation.hh"
#include "../AnimatedSprite.hh"
#include "../Character.hh"

class Monster : public Character {
public:
    Monster();
    void SetAnimatedSprite(AnimatedSprite);
private:
};

#endif //LITTLEBIGGAME_MONSTER_HH
