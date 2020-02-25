
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

class Worm : public Character {
private:

    sf::Sprite sprite;
    Bullet* bullet;

public:
    bool hasshot = false;

    explicit Worm(std::vector<Animation> animations);

    sf::Vector2f getPosition() const;

    void move(Direction d) override;

    void update(sf::Time frameTime) override;

    void draw(sf::RenderWindow &window) override;

    Bullet &getBullet() const;
};

#endif //LITTLEBIGGAME_WORM_HH
