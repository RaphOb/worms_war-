
#ifndef LITTLEBIGGAME_WORM_HH
#define LITTLEBIGGAME_WORM_HH


#include <SFML/System.hpp>

enum Direction {
    RIGHT, LEFT
};

class Worm {
private:
    /**
     * @var Position on the X axis, maybe
     */
    double m_x;
    /**
     * @ar Position on the Y axis, maybe
     */
    double m_y;
    /**
     * @var
     */
    sf::Vector2f m_movement;
    /**
     * @var Speed of the worm
     */
    double m_speed;
    /**
     * @var Velocity for jumping
     */
     sf::Vector2f m_velocity;
     /**
      * @var
      */
     bool m_canJump;
     /**
      * @var
      */
      float m_jumpHeight;
public:
    Worm();
    sf::Vector2f getMovement() const;
    void resetMovement();
    void move(Direction d);
    void jump();
};
#endif //LITTLEBIGGAME_WORM_HH
