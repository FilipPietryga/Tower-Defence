#include "pch.h"

#pragma once
class Enemy : public Entity
{
public:
	Enemy()
		: _position(sf::Vector2f(0,0)), _size(sf::Vector2f(0,0)), _speed(sf::Vector2f(0,0)), _color(sf::Color::Transparent), step(0), _finished(false), _killed(false) {};
	Enemy(sf::Vector2f position, sf::Vector2f size, sf::Vector2f speed, sf::Color color)
		: Entity("enemy"), _size(size), _position(position), _speed(speed), _color(color), _finished(false), _killed(false) {};
	~Enemy();

	void draw(sf::RenderWindow& window)
	{
		sf::RectangleShape rectShape;
		rectShape.setPosition((float)_position.x, (float)_position.y);
		rectShape.setSize(_size);
		rectShape.setFillColor(sf::Color::Yellow);
		window.draw(rectShape);
	}
	void update(std::vector<sf::Vector2i>* _path)
	{
		_position += _speed;
		if(!_finished || !_killed) {
			if (_path->operator[](step).x * 40 + 15 <= (int)_position.x && _path->operator[](step).x * 40 + 40 - 15 >= (int)_position.x
				&& _path->operator[](step).y * 40 + 15 <= (int)_position.y && _path->operator[](step).y * 40 + 40 - 15 >= (int)_position.y) {
				if (step >= _path->size() - 1)
				{
					_finished = true;
					_speed = sf::Vector2f(0, 0);
				}
				else {
					step += 1;
					sf::Vector2i diff = (_path->operator[](step) - _path->operator[](step - 1));
					_speed = sf::Vector2f(diff.x, diff.y);
				}
			}
		}
	}
	void changeDir(sf::Vector2f speed)
	{
		this->_speed = speed;
	}
	Enemy& setSize(sf::Vector2f size)
	{
		_size = size;
		return *this;
	}
	Enemy& setPosition(sf::Vector2f position)
	{
		_position = position;
		return *this;
	}
	Enemy& setSpeed(sf::Vector2f speed)
	{
		_speed = speed;
		return *this;
	}

	sf::Vector2f _position;
	sf::Vector2f _size;
	sf::Vector2f _speed;
	sf::Color _color;
	int step;
	bool _finished;
	bool _killed;
};

