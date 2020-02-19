#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ISerializable.hh"

class AbstractEntity : public ISerializable, public sf::Drawable {
public:
	AbstractEntity() = default;
	AbstractEntity(sf::RectangleShape body);
	virtual ~AbstractEntity() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(sf::Time frameTime) = 0;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::RectangleShape* m_body;
};