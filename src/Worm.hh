
#ifndef LITTLEBIGGAME_WORM_HH
#define LITTLEBIGGAME_WORM_HH


#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "Character.hh"
#include "AnimatedSprite.hh"
#include "Collider.hh"
#include "Bullet.hh"
#include "Direction.hh"
#include "IObserver.hh"


class Worm : public Character, public IObserver {
private:

    sf::Sprite sprite;
    Bullet* bullet;
    float angle;
    double distance_covered;
    sf::Clock bulletTime;
    bool m_noKeyWasPressed = true;


public:
    bool hasshot = false;

    explicit Worm(std::vector<Animation> animations);

    sf::Vector2f getPosition() const;

    void move(Direction d) override;

    void update(sf::Time frameTime) override;

    void draw(sf::RenderWindow &window) override;
    void onNotify(Direction) override;

    Bullet &getBullet() const;
};

#endif //LITTLEBIGGAME_WORM_HH
