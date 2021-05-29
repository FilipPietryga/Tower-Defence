#include "pch.h"
#include "Tile.h"
#include <typeinfo>
#include "Tower.h"
#include "Route.h"

Tile::Tile()
{
	_position = nullptr;
	_size = nullptr;
	_color = nullptr;
	_entity = nullptr;
}

Tile::Tile(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
	: _position(const_cast<sf::Vector2f*>(&position)), _size(const_cast<sf::Vector2f*>(&size)), _color(const_cast<sf::Color*>(&color))
{	
	_entity = nullptr;
}

Tile& Tile::setPosition(const sf::Vector2f& position)
{
	this->_position = const_cast<sf::Vector2f*>(&position);
	return *this;
}

Tile& Tile::setPosition(float x, float y)
{
	this->_position = new sf::Vector2f(x, y);
	return *this;
}

Tile& Tile::setSize(const sf::Vector2f& size)
{
	this->_size = const_cast<sf::Vector2f*>(&size);
	return *this;
}

Tile& Tile::setSize(float x, float y)
{
	this->_size = new sf::Vector2f(x, y);
	return *this;
}

Tile& Tile::setFillColor(const sf::Color& color)
{
	_color = const_cast<sf::Color*>(&color);
	return *this;
}

Tile& Tile::setEntity(Entity& entity)
{
	if (typeid(entity).name() == typeid(Tower).name()) {
		_entity = new Tower(*(dynamic_cast<Tower*>(&entity)));
	}
	if (typeid(entity).name() == typeid(Route).name()) {
		_entity = new Route(*(dynamic_cast<Route*>(&entity)));
	}
	return *this;
}

void Tile::draw(sf::RenderWindow& window)
{
	sf::RectangleShape rectShape;
	rectShape.setPosition(_position->x, _position->y);
	rectShape.setSize(sf::Vector2f(_size->x, _size->y));
	rectShape.setFillColor(*_color);
	window.draw(rectShape);
	if (_entity) {
		_entity->draw(window);
	}
}


Tile::~Tile()
{

}