//
// Created by lafay on 18/02/2020.
//

#ifndef LITTLEBIGGAME_MONSTER_HH
#define LITTLEBIGGAME_MONSTER_HH

#include "../Animation.hh"
#include "../AnimatedSprite.hh"
#include "../Character.hh"
#include "../Collider.hh"
#include "../PathFinding/Pathfinding.hh"

class Monster : public Character {
public:
    explicit Monster(std::vector<Animation>, const sf::Vector2f&, Pathfinding*);

    sf::Vector2f getPosition() const;

    void move(Direction) override ;

    void update(sf::Time) override;

    void draw(sf::RenderWindow &) override;

    Pathfinding *getPathfinding();
private:
    Pathfinding *m_pathfinding;
    Node *m_currentNode;
};

#endif //LITTLEBIGGAME_MONSTER_HH
