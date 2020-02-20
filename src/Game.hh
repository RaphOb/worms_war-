//
// Created by geoff on 19/02/2020.
//

#ifndef LITTLEBIGGAME_GAME_HH
#define LITTLEBIGGAME_GAME_HH


#include <SFML/Graphics/Texture.hpp>
#include "Worm.hh"

class Game {
private:
    sf::Texture m_walkingTexture;
    sf::Texture m_jumpingTexture;
    sf::RectangleShape shape;

public:
    Game();
    bool initTextures();
    Worm initWorm();
};


#endif //LITTLEBIGGAME_GAME_HH
