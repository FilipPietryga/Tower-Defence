#include "pch.h"
#include "Entity.h"
#include "FileLoadException.h"

Entity::Entity()
	: _position(sf::Vector2f(0,0)), _name("Entity"), _texture(nullptr)
{
	_texture = nullptr;
}

Entity::Entity(const char* name)
	: _name(name), _texture(nullptr), _position(0,0)
{
	_name = name;
}

Entity::Entity(const Entity& source)
	: _position(source._position), _name(source._name), _texture(source._texture)
{

}

Entity& Entity::operator=(const Entity& source)
{
	if (this == &source)
		return *this;
	this->_position = source._position;
	return *this;
}

Entity::~Entity()
{

}

sf::Vector2i& Entity::getPosition()
{
	return this->_position;
}

sf::Texture* Entity::getTexture()
{
	return this->_texture;
}

const char* Entity::getName()
{
	return _name;
}

Entity& Entity::setPosition(int x, int y)
{
	this->_position = sf::Vector2i(x, y);
	return *this;
}

Entity& Entity::setTexture(std::string filename)
{
	sf::Texture *texture = new sf::Texture;
	if (!texture->loadFromFile(filename))
	{
		throw FileLoadException().setFilename("Entity.cpp")
			.setFilename("Entity& Entity::setTexture(std::string filename)")
			.setLine(__LINE__)
			.setInfo("The filename provided to the function was wrong; there is no such file \
					  in the directory or there was an error while opening that file")
			.setResourcePath(filename.c_str());
	}
	_texture = texture;
	return *this;
}