#pragma once
#include "Tile.h"

namespace mb {

	class MapBuilder
	{
	public:
		MapBuilder(sf::Vector2i startPos, sf::Vector2i endPos, sf::Vector2i mapSize);
		std::vector<sf::Vector2i> build(Tile** tile);
	protected:
		sf::Vector2i _startPos;
		sf::Vector2i _endPos;
		sf::Vector2i _mapSize;
	};

}