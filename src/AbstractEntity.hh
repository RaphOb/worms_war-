#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "ISerializable.hh"

class AbstractEntity : public ISerializable {
public:
	AbstractEntity() = default;
	virtual ~AbstractEntity() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update(sf::Time frameTime) = 0;

};