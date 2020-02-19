
#ifndef LITTLEBIGGAME_WORM_HH
#define LITTLEBIGGAME_WORM_HH


#include <SFML/System.hpp>
#include <iostream>
#include "Character.hh"
#include "AnimatedSprite.hh"
#include "Collider.hh"
#include "Bullet.hh"

enum Direction {
    RIGHT = 0, LEFT = 1, JUMP = 2
};

class Worm : public Character {
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
    sf::Sprite sprite;
    int leftorright;
    sf::Clock lastShot{};
    std::unique_ptr<Bullet> bullet;
    bool hasshot = false;

    sf::Texture bazookaTexture;
    std::vector<sf::IntRect> left = {
            sf::IntRect(0, 0, 50, 34)
    };
    std::vector<sf::IntRect> right = {
            sf::IntRect(50, 0, 50, 34)
    };

    int textureLoad() {
        if (!bazookaTexture.loadFromFile("../resources/bazooka.png")) {
            std::cout << "Failed to load worms spritesheet!" << std::endl;
            return -1;
        }
    };



    sf::RectangleShape* body;
public:
//    Worm();
    explicit Worm(AnimatedSprite animatedSprite, std::vector<Animation> animations);

    sf::Vector2f getVelocity() const;

    void move(Direction d);

    sf::Vector2f getPosition() const;

    bool canJump() const;

    void setYVelocity(float v);

    void onCollision(sf::Vector2f direction);

    Collider getCollider();

    void update(sf::Time frameTime, sf::RenderWindow&);

    void draw(sf::RenderWindow &window) override;
};

#endif //LITTLEBIGGAME_WORM_HH
