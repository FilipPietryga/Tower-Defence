#pragma once
#include "Entity.h"

class Route : public Entity
{
public:
	Route();
	Route(const Route&);
	void draw(sf::RenderWindow& window);
	~Route();
};