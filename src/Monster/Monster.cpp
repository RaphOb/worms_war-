//
// Created by lafay on 18/02/2020.
//

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Monster.hh"
#include "../Animation.hh"
#include "../AnimatedSprite.hh"
#include "../Character.hh"
#include "../Constant.hh"
#include "../Map.hh"

using namespace std;

Monster::Monster(std::vector<Animation> animations, const sf::Vector2f& position, Pathfinding* pathfinding) :
    Character(100,
              std::move(animations),
              AnimatedSprite(sf::seconds(0.1), true, true),
              sf::Vector2f(0.f, 0.f),
              100.f,
              300.f) {
        m_pathfinding = pathfinding;
        m_body->setOrigin(m_currentAnimation->getFrame(0).width / 2.f, m_currentAnimation->getFrame(0).height / 2.f);
        m_body->setPosition(position);
}


void Monster::draw(sf::RenderWindow &window) {
    window.draw(m_animatedSprite);
}

void Monster::move(Direction d) {
    if (d == RIGHT) {
        m_velocity.x += m_speed;
        m_orientation = RIGHT;
        m_currentAnimation = &m_animations[RIGHT];
    } else if (d == LEFT) {
        m_velocity.x -= m_speed;
        m_orientation = LEFT;
        m_currentAnimation = &m_animations[LEFT];
    } else if (d == UP) {
        m_velocity.y -= m_speed;
    } else if (d == DOWN) {
        m_velocity.y += m_speed;
    }
}

void Monster::update(sf::Time frameTime) {
    m_velocity.x = 0.0f;
    m_velocity.y = 0.0f;

    Node *currentNode = getPathfinding()->getMap()->getNodeByPos(std::floor(getPosition().y/Constant::BLOCK_SIZE), std::floor(getPosition().x/Constant::BLOCK_SIZE));
    std::vector<Direction> directions;
    if ((int)this->getPosition().x != currentNode->getX()*(int)Constant::BLOCK_SIZE+15 && (int)this->getPosition().y != currentNode->getY()*(int)Constant::BLOCK_SIZE+15 && !m_old_directions.empty() ) {
        directions = m_old_directions;
    } else {
        directions = getPathfinding()->getDirection(currentNode);
        m_old_directions = directions;
    }

    for (auto &dir : directions) {
        move(dir);
    }

    m_animatedSprite.play(*m_currentAnimation);
    m_body->move(m_velocity * frameTime.asSeconds());

    m_animatedSprite.update(frameTime);
}

sf::Vector2f Monster::getPosition() const {
    return m_body->getPosition();
}

void Monster::onDestroy() {
    delete(this);

}

Monster::~Monster() {

}

Pathfinding *Monster::getPathfinding() {
    return m_pathfinding;
}
