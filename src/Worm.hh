
#ifndef LITTLEBIGGAME_WORM_HH
#define LITTLEBIGGAME_WORM_HH


#include <SFML/System.hpp>
#include "Character.hh"
#include "AnimatedSprite.hh"
#include "Collider.hh"
#include "Direction.hh"

class Worm : public Character {
private:


public:
    explicit Worm(std::vector<Animation> animations);

    sf::Vector2f getPosition() const;

    void update(sf::Time frameTime) override;

//    void draw(sf::RenderWindow &window) override;
};

#endif //LITTLEBIGGAME_WORM_HH
