#ifndef STEP01_CHARACTER_HH
#define STEP01_CHARACTER_HH

#include <list>
#include "AbstractEntity.hh"
#include "IObservable.hh"

class Character: public AbstractEntity, public IObservable {
private:
    /**
     * @var Life of the character
     */
    int m_life;
    /**
     * @var Position on the X axis, maybe
     */
    double m_x;
    /**
     * @ar Position on the Y axis, maybe
     */
    double m_y;
    /**
     * @var List of observers that would be notify when change occurs
     */
    std::list<IObserver*> m_observers;
public:
    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    int getLife() const;

    void setLife(int life);

protected:
    Character();
    explicit Character(int l) : m_life(l), m_x(0), m_y(0) {};
    Character(int l, double _x, double _y) : m_life(l), m_x(_x), m_y(_y) {};
public:
    virtual ~Character() = default;
    void draw(sf::RenderWindow& window) override ;
    void update(sf::Time frameTime) override ;
    void AddObserver(IObserver *obs) override ;
    void RemoveObserver(IObserver *obs) override ;
    void NotifyAll();
    std::string Serialize() override ;
};


#endif //STEP01_CHARACTER_HH
