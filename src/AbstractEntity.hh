#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ISerializable.hh"

class AbstractEntity : public ISerializable, public sf::Drawable {
public:
	explicit AbstractEntity();
	explicit AbstractEntity(sf::RectangleShape* body);
	virtual ~AbstractEntity() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(sf::Time frameTime) = 0;
	virtual void onCollision(sf::Vector2f direction) = 0;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

protected:
    sf::RectangleShape* m_body;
};