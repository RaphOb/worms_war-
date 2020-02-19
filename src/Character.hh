#ifndef STEP01_CHARACTER_HH
#define STEP01_CHARACTER_HH

#include <list>
#include "AbstractEntity.hh"
#include "IObservable.hh"
#include "Animation.hh"
#include "AnimatedSprite.hh"

class Character : public AbstractEntity, public IObservable {
private:
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

    /**
     * List of observers that would be notify when change occurs
     */
    std::list<IObserver *> m_observers;
public:


    int getLife() const;

    void setLife(int life);

protected:
    Character();

    explicit Character(int l, sf::RectangleShape body);
public:
    virtual ~Character() = default;

    void draw(sf::RenderWindow &window) override;

//    virtual void update(sf::Time frameTime) = 0;

    void AddObserver(IObserver *obs) override;

    void RemoveObserver(IObserver *obs) override;

    void NotifyAll();

    std::string Serialize() override;
};


#endif //STEP01_CHARACTER_HH
