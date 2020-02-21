//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_MONSTERFACTORY_HH
#define LITTLEBIGGAME_MONSTERFACTORY_HH

#include "../Character.hh"
#include "../AnimatedSprite.hh"
#include "Monster.hh"

class MonsterFactory {
public:
    MonsterFactory();
    Monster* Create(const std::string&, const sf::Vector2f&);
    bool initTextures();

private:
    sf::Texture m_walkingTexture;
    sf::Texture m_jumpingTexture;
};

#endif //LITTLEBIGGAME_MONSTERFACTORY_HH
