//
// Created by geoff on 19/02/2020.
//

#ifndef LITTLEBIGGAME_GAME_HH
#define LITTLEBIGGAME_GAME_HH


#include <SFML/Graphics/Texture.hpp>
#include "Worm.hh"
#include "Platform.hh"
#include "Map.hh"

class Game {
private:
    sf::Texture m_walkingTexture;
    sf::Texture m_jumpingTexture;
    sf::RectangleShape shape;
    TimeManager tm;
    sf::RectangleShape m_rectGameTime;
    sf::Text m_textGameTime;
    sf::Font m_font;
    Map m_map;

public:
    Game();
    bool initTextures();
    Worm initWorm();
    void update(sf::RenderWindow &);
    void draw(sf::RenderWindow& window);
    string getFormatGameTime();
    Map getMap();
};


#endif //LITTLEBIGGAME_GAME_HH
