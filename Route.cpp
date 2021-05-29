#include "pch.h"
#include "Route.h"

Route::Route()
	: Entity("Route")
{
	_position = sf::Vector2i(0,0);
	_texture = nullptr;
	_name = "Route";
}


Route::Route(const Route& src)
	: Entity(src)
{
	_position = src._position;
	_texture = src._texture;
	_name = "Route";
}

Route::~Route()
{
	delete _texture;
}

void Route::draw(sf::RenderWindow& window)
{
	/*sf::Sprite sprite;
	sprite.setPosition((float)this->_position.x, (float)this->_position.y);
	sprite.setTexture(*(this->_texture), false);
	window.draw(sprite);*/

	sf::RectangleShape rs;
	rs.setPosition((float) this->_position.x, (float) this->_position.y);
	rs.setFillColor(sf::Color::Blue);
	rs.setSize(sf::Vector2f(40.0f, 40.0f));
	window.draw(rs);
}