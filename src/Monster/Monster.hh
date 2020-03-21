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
    explicit Monster(std::vector<Animation>, const sf::Vector2f&);
    ~Monster();

    sf::Vector2f getPosition() const;

    void move(Direction) override ;

    void update(sf::Time) override;

    void draw(sf::RenderWindow &) override;

    void onDestroy();

    bool isDestroyed = false;
private:

};

#endif //LITTLEBIGGAME_MONSTER_HH
