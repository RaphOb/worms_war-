//
// Created by geoff on 13/02/2020.
//

#ifndef LITTLEBIGGAME_PLATFORM_HH
#define LITTLEBIGGAME_PLATFORM_HH


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Collider.hh"
#include "Monster/Spawner.hh"
#include "TimeManager.hh"

class Platform : public AbstractEntity {
public:
    Platform(sf::Vector2f size, sf::Vector2f pos, MonsterFactory *, bool isWall);

    void draw(sf::RenderWindow& window) override;
    void update(sf::Time frameTime) override;
    Collider getCollider();
    void setSpawnerDifficulty(int);
    Spawner getSpawner();
    std::string Serialize() override;
    void onCollision(sf::Vector2f direction) override;
    void onCollision(sf::Vector2f direction, bool);
    unsigned int getPercentCurse();
    void initTextureRect(sf::Vector2f size);
    void initText(sf::Vector2f);
    void resetOnWalk();
    sf::Vector2f getPos();
    sf::Vector2f getSize();

private:
    int m_countDownToSpawner;
    int m_initialCountDownToSpawner;
    Spawner m_spawner;
    bool m_isSpawner;
    bool m_isWall;
    TimeManager tm;
    sf::Text* m_text;

};


#endif //LITTLEBIGGAME_PLATFORM_HH
