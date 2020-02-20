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
    explicit Monster(AnimatedSprite animatedSprite, std::vector<Animation> animations);
    void onCollision(sf::Vector2f direction);
    Collider getCollider();
    sf::Vector2f getPosition() const;
    void update(sf::Time frameTime) override;
    void draw(sf::RenderWindow &window) override;
    //void SetAnimatedSprite(AnimatedSprite);
private:
    /**
     * @var
     */
    std::vector<Animation> m_animations;
    /**
     * @var Current animation
     */
    Animation *m_currentAnimation;
    /**
     * @var
     */
    AnimatedSprite m_animatedSprite;
    /**
     * @var Velocity for moving
     */
    sf::Vector2f m_velocity;
    /**
     * @var Speed of the worm
     */
    double m_speed;
    /**
     * @var Boolean to know when the worm can jump or not
     */
    bool m_canJump;
    /**
     * @var Height of the jump
     */
    float m_jumpHeight;

    int m_orientation;


    sf::RectangleShape* body;
};

#endif //LITTLEBIGGAME_MONSTER_HH
