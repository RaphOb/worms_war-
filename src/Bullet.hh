//
// Created by oraph on 19/02/2020.
//

#ifndef LITTLEBIGGAME_BULLET_HH
#define LITTLEBIGGAME_BULLET_HH


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Collider.hh"

class Bullet {
public:
    Bullet();
    ~Bullet();
    void fireBullet(sf::Vector2f position);
    Collider getCollider();


private:
    sf::RectangleShape body;
    sf::Texture texture;

};


#endif //LITTLEBIGGAME_BULLET_HH
