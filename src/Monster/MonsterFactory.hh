//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_MONSTERFACTORY_HH
#define LITTLEBIGGAME_MONSTERFACTORY_HH

#include "../Character.hh"
#include "../AnimatedSprite.hh"

class MonsterFactory {
public:
    MonsterFactory();
    Character* Create(const std::string&);
    bool initTextures();

private:
    sf::Texture m_walkingTexture;
    sf::Texture m_jumpingTexture;
    sf::RectangleShape shape;
};

#endif //LITTLEBIGGAME_MONSTERFACTORY_HH
