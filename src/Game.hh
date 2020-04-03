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
    TimeManager tm;
    sf::RectangleShape m_rectGameTime;
    sf::Text m_textGameTime;
    sf::Text m_textFPS;
    sf::Text m_textLife;
    Map m_map;

public:
    Game();
    Worm initWorm();
    void update(sf::RenderWindow &);
    void draw(sf::RenderWindow& window);
    void drawGameOver(sf::RenderWindow& window);
    string getFormatGameTime();
    Map getMap();

    void setFPS(int fps);
    void setLife(int life);
};


#endif //LITTLEBIGGAME_GAME_HH
