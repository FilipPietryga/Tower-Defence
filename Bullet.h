#include "Entity.h"
#pragma once
class Bullet : public Entity
{
public:
	Bullet(sf::Vector2f position, sf::Vector2f size, sf::Vector2f speed)
		: Entity()
	{
		_position = position;
		_size = size;
		_speed = speed;
	}
	void draw(sf::RenderWindow& window)
	{
		sf::RectangleShape rectShape;
		rectShape.setPosition((float)_position.x, (float)_position.y);
		rectShape.setSize(_size);
		rectShape.setFillColor(sf::Color::Black);
		window.draw(rectShape);
	}
	void update()
	{
		_position += _speed;
		if (_position.x < 0 || _position.x > 640 || _position.y < 0 || _position.y > 640)
		{
			toDelete = true;
		}
	}

	bool getToDelete()
	{
		return toDelete;
	}
	bool toDelete = false;
	sf::Vector2f _position;
	sf::Vector2f _speed;
};

