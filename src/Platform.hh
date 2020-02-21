//
// Created by geoff on 13/02/2020.
//

#ifndef LITTLEBIGGAME_PLATFORM_HH
#define LITTLEBIGGAME_PLATFORM_HH


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Collider.hh"
#include "Monster/Spawner.hh"
#include "TimeManager.hh"

class Platform : public AbstractEntity {
public:
    Platform(sf::Vector2f size, sf::Vector2f pos, bool isSpawner);

    void draw(sf::RenderWindow& window) override;
    void update(sf::Time frameTime) override;
    Collider getCollider();
    void setSpawnerDifficulty(int);
    Spawner getSpawner();
    std::string Serialize() override;
    void onCollision(sf::Vector2f direction) override;
private:
    sf::RectangleShape body;
    sf::RectangleShape shape;
    int m_countDownToSpawner;
    Spawner m_spawner;
    bool m_isSpawner;
    TimeManager tm;

};


#endif //LITTLEBIGGAME_PLATFORM_HH
