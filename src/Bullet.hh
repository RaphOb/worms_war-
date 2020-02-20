//
// Created by oraph on 19/02/2020.
//

#ifndef LITTLEBIGGAME_BULLET_HH
#define LITTLEBIGGAME_BULLET_HH


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Collider.hh"

class Bullet {
public:
    Bullet();
    ~Bullet();
    void fireBullet(sf::Vector2f position, int leftorright);
    Collider getCollider();
    void update(int leftorright);
    void draw(sf::RenderWindow& window);


private:
    sf::RectangleShape* body;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Clock clock1;

};


#endif //LITTLEBIGGAME_BULLET_HH
