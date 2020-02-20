//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_MONSTER_HH
#define LITTLEBIGGAME_MONSTER_HH

#include "../Animation.hh"
#include "../AnimatedSprite.hh"
#include "../Character.hh"
#include "../Collider.hh"

class Monster : public Character {
public:
    explicit Monster(std::vector<Animation> animations);

    sf::Vector2f getPosition() const;

    void move(Direction d) override ;

    void update(sf::Time frameTime) override;

    void draw(sf::RenderWindow &window) override;
private:

};

#endif //LITTLEBIGGAME_MONSTER_HH
