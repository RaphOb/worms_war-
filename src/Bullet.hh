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
#include "AbstractEntity.hh"

class Bullet: public AbstractEntity {
public:
    Bullet(int);
    ~Bullet() override;
    void fireBullet(sf::Vector2f position);
    Collider getCollider();
    void update();
    void draw(sf::RenderWindow& window)  ;
    void update(sf::Time frameTime) override ;
    std::string Serialize() override ;
    void  onCollision(sf::Vector2f direction) override;


private:
//    sf::RectangleShape* body;
    sf::Clock clock1;
    float speed =  35;
    int m_orientation;

};


#endif //LITTLEBIGGAME_BULLET_HH
