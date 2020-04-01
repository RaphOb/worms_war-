#ifndef STEP01_CHARACTER_HH
#define STEP01_CHARACTER_HH

#include <list>
#include "AbstractEntity.hh"
#include "Animation.hh"
#include "AnimatedSprite.hh"
#include "Collider.hh"
#include "Direction.hh"
//#include "Worm.hh"

class Worm;

class Character : public AbstractEntity {
protected:
    /**
     * @var Life of the character
     */
    int m_life;
    /**
     *
     */
    std::vector<Animation> m_animations;
    /**
     *
     */
    Animation *m_currentAnimation;
    /**
     *
     */
    AnimatedSprite m_animatedSprite;
    /**
    *
    */
    sf::Vector2f m_velocity;
    /**
    *
    */
    double m_speed;
    /**
    *
    */
    bool m_canJump;
    /**
    *
    */
    float m_jumpHeight;
    /**
    *
    */
    int m_orientation;

public:


    int getLife() const;

    void setLife(int life);

protected:
    Character();
    explicit Character(int l, std::vector<Animation> animations, AnimatedSprite animatedSprite, sf::Vector2f velocity,
            float speed, float jumpHeight);
public:
    virtual ~Character() = default;

    void draw(sf::RenderWindow &window) override;

//    virtual void update(sf::Time frameTime) = 0;

    bool canJump() const;

    void onCollision(sf::Vector2f direction) override ;

    Collider getCollider();

    virtual void move(Direction d);

    std::string Serialize() override;
};


#endif //STEP01_CHARACTER_HH
