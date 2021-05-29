#include "Entity.h"

#pragma once
class Tile
{
public:
	Tile();
	Tile(const sf::Vector2f&, const sf::Vector2f&, const sf::Color&);
	~Tile();
public:
	void draw(sf::RenderWindow&);
	Tile& setPosition(const sf::Vector2f&);
	Tile& setPosition(float, float);
	Tile& setSize(const sf::Vector2f&);
	Tile& setSize(float, float);
	Tile& setFillColor(const sf::Color&);
	Tile& setEntity(Entity&);
public:
	sf::Vector2f* _position;
	sf::Vector2f* _size;
	sf::Color* _color;
	Entity* _entity;
};

