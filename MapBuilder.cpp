#include "pch.h"
#include "MapBuilder.h"
#include "Route.h"
#include "AStar.h"
#include <time.h>
#include <chrono>

namespace mb {

	MapBuilder::MapBuilder(sf::Vector2i startPos, sf::Vector2i endPos, sf::Vector2i mapSize)
		: _startPos(startPos), _endPos(endPos), _mapSize(mapSize)
	{	}

	std::vector<sf::Vector2i> MapBuilder::build(Tile **tile)
	{
		std::cout << "Start:" << _startPos.x << " " << _startPos.y << std::endl;
		std::cout << "End:" << _endPos.x << " " << _endPos.y << std::endl;
		/*sf::Vector2i currentPos = _startPos;

		while (currentPos.x != _endPos.x || currentPos.y != _endPos.y) {
			Route route;
			tile[currentPos.x][currentPos.y].setEntity(route);
			if(currentPos.x != _endPos.x)
			{
				if (currentPos.y != _endPos.y)
				{
					rand()%
				}
			}
		}*/
		pf::AStar astar;
		astar.setDimentions(_mapSize);
		astar.setDiagonalMovement(false);
		std::vector<sf::Vector2i> result;
		//auto now = std::chrono::
		int limit = 70;
		do {
			astar.setGridToRandom();
			result = astar.findPath(_startPos, _endPos, pf::heuristic::manhattan, 1);
			_startPos = sf::Vector2i(0, rand() % _mapSize.y);
			_endPos = sf::Vector2i(_mapSize.x - 1, rand() % _mapSize.y);
			limit--;
		} while (result.size() < limit);
		for (std::vector<sf::Vector2i>::iterator it = result.begin(); it != result.end(); it++)
		{
			Route route;
			route.setPosition((float)(*it).x * 40.0f, (float)(*it).y * 40.0f);
			Tile temp = tile[(*it).x][(*it).y].setEntity(route);
			tile[(*it).x][(*it).y] = temp;
			std::cout << (*it).x << " " << (*it).y << " -> ";
		}
		return result;
	}	
}