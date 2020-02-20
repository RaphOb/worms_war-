//
// Created by geoff on 13/02/2020.
//

#ifndef LITTLEBIGGAME_COLLIDER_HH
#define LITTLEBIGGAME_COLLIDER_HH


#include <SFML/Graphics/RectangleShape.hpp>

class Collider {
public:
    Collider(sf::RectangleShape* body);



    bool checkCollision(Collider& other, sf::Vector2f& direction, float push);
    sf::Vector2f getPosition();
    sf::Vector2f getHalfSize();
    void move(float dx, float dy);

private:
    sf::RectangleShape* body;
};


#endif //LITTLEBIGGAME_COLLIDER_HH
