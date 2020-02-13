//
// Created by geoff on 13/02/2020.
//

#ifndef LITTLEBIGGAME_PLATFORM_HH
#define LITTLEBIGGAME_PLATFORM_HH


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Collider.hh"

class Platform {
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos);

    void draw(sf::RenderWindow& window);
    Collider getCollider();
private:
    sf::RectangleShape body;
};


#endif //LITTLEBIGGAME_PLATFORM_HH
