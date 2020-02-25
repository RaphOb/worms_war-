//
// Created by oraph on 22/02/2020.
//

#ifndef LITTLEBIGGAME_BOOM_HH
#define LITTLEBIGGAME_BOOM_HH


#include <SFML/System/Vector2.hpp>
//#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Animation.hh"
#include "AnimatedSprite.hh"
#include "Character.hh"
#include <thread>

class Boom : public AbstractEntity {
private:
    std::vector<Animation> m_animations;
    Animation *m_currentAnimation{};
    AnimatedSprite m_animatedSprite;
    float age{0};
    static constexpr float LIFE_TIME{2.5f};

public:
    void makeBoom(sf::Vector2f);

    Boom(const Boom &other);

    Boom(std::vector<Animation>, sf::Vector2f, AnimatedSprite);

    void draw(sf::RenderWindow &window) override;

    void update(sf::Time frameTime) override;

    void onCollision(sf::Vector2f direction) override;

    std::string Serialize() override;

    void loopAnimmation(sf::RenderWindow &window,sf::Time frameTime);

    void setPosition(float,float);

};


#endif //LITTLEBIGGAME_BOOM_HH
