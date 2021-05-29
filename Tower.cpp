#include "pch.h"
#include "Tower.h"
#include "Entity.h"

Tower::Tower()
	: Entity("Tower")
{   }

Tower::Tower(const Tower& src)
	: Entity(src)
{   
	_position = src._position;
	_texture = src._texture;
}

Tower& Tower::operator=(const Tower& src)
{
	return *this;
}

Tower::~Tower()
{

}

void Tower::draw(sf::RenderWindow& window) 
{
	sf::Sprite sprite;
	sprite.setPosition((float) this->_position.x, (float) this->_position.y);
	sprite.setTexture(*(this->_texture), false);
	window.draw(sprite);
}