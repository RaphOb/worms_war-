
#ifndef LITTLEBIGGAME_WORM_HH
#define LITTLEBIGGAME_WORM_HH


#include <SFML/System.hpp>
#include "Character.hh"
#include "AnimatedSprite.hh"
#include "Collider.hh"
#include "Direction.hh"

class Worm : public Character {
private:
    /**
     * @var
     */
//    std::vector<Animation> m_animations;
    /**
     * @var Current animation
     */
//    Animation *m_currentAnimation;
    /**
     * @var
     */
//    AnimatedSprite m_animatedSprite;
    /**
     * @var Velocity for moving
     */
//    sf::Vector2f m_velocity;
    /**
     * @var Speed of the worm
     */
//    double m_speed;
    /**
     * @var Boolean to know when the worm can jump or not
     */
//    bool m_canJump;
    /**
     * @var Height of the jump
     */
//    float m_jumpHeight;

//    int m_orientation;


    sf::RectangleShape* body;
public:
//    Worm();
    explicit Worm(AnimatedSprite animatedSprite, std::vector<Animation> animations);

    sf::Vector2f getVelocity() const;

    void move(Direction d) override ;


    sf::Vector2f getPosition() const;

//    bool canJump() const;

    void setYVelocity(float v);

//    void onCollision(sf::Vector2f direction);
//
//    Collider getCollider();

    void update(sf::Time frameTime) override;

//    void draw(sf::RenderWindow &window) override;
};

#endif //LITTLEBIGGAME_WORM_HH
