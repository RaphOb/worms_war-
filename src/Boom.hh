//
// Created by oraph on 22/02/2020.
//

#ifndef LITTLEBIGGAME_BOOM_HH
#define LITTLEBIGGAME_BOOM_HH


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Animation.hh"
#include "AnimatedSprite.hh"
#include "Character.hh"

class Boom : public Character {
private:

public:
    void makeBoom(sf::Vector2f);

    Boom(std::vector<Animation>, sf::Vector2f);

    void draw(sf::RenderWindow &window) override;

    void update(sf::Time frameTime) override;

};


#endif //LITTLEBIGGAME_BOOM_HH
