#pragma once
#include "pch.h"
class Entity
{
public:
	Entity();
	Entity(const char* name);
	Entity(const Entity&);
	Entity& operator=(const Entity&);
	~Entity();
	virtual void draw(sf::RenderWindow&) = 0;
	Entity& setPosition(int, int);
	Entity& setTexture(std::string);
	sf::Vector2i& getPosition();
	sf::Texture* getTexture();
	const char* getName();
	Entity& setSize(sf::Vector2f size)
	{
		_size = size;
		return *this;
	}
protected:
	sf::Vector2i _position;
	sf::Texture* _texture;
	const char* _name;
	sf::Vector2f _size;
};