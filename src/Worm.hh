
#ifndef LITTLEBIGGAME_WORM_HH
#define LITTLEBIGGAME_WORM_HH


#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include "Character.hh"
#include "AnimatedSprite.hh"
#include "Collider.hh"
#include "Direction.hh"

class Worm : public Character {
private:

    sf::Sprite sprite;
    int leftorright;
    sf::Clock lastShot{};

    sf::Texture bazookaTexture;
    int textureLoad() {
        if (!bazookaTexture.loadFromFile("../resources/bazooka.png")) {
            std::cout << "Failed to load worms spritesheet!" << std::endl;
            return -1;
        }
    };

public:
    explicit Worm(std::vector<Animation> animations);

    sf::Vector2f getPosition() const;

    void move(Direction d) override ;

    void update(sf::Time frameTime) override;

    void draw(sf::RenderWindow &window) override;
};

#endif //LITTLEBIGGAME_WORM_HH
