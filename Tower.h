#include "Entity.h"
#include "AStar.h"
#include "Enemy.h"

#pragma once
class Tower : public Entity
{
public:
	Tower();
	Tower(const Tower&);
	Tower& operator=(const Tower&);
	~Tower();
	void draw(sf::RenderWindow&) override;
	void attack(Entity** enemies, std::vector<Bullet*> *bullets) //czy jakbym tutaj przekazal przez tablicê przeciwnikow 
								  //to konwersja nastapilaby bez pozniejszej korekty
	{
		unsigned int minimal = 9999999999;
		int targeted = 0;
		int index = -1;
		for (int i = 0; i < 10; i++)
		{
			index++;
			if (enemies[i])
			{
				break;
			}
		}
		if (index < 10) {
			if (enemies[index]) {
				targeted = index;
				Enemy* enemy = dynamic_cast<Enemy*>(enemies[index]);
				minimal = pf::heuristic::euclidean(this->_position, sf::Vector2i((int)enemy->_position.x, (int)enemy->_position.y), 1);
			}
			for (int i = index + 1; i < 10; i++)
			{
				Enemy *enemy = dynamic_cast<Enemy*>(enemies[i]);
				unsigned int length = pf::heuristic::euclidean(this->_position, sf::Vector2i((int)enemy->_position.x, (int)enemy->_position.y), 1);
				if (length < minimal)
				{
					minimal = length;
				}
			}
		}
		std::cout << minimal << std::endl;
		if (minimal < 150)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(enemies[targeted]);
			float diffx = enemy->_position.x - _position.x;
			float diffy = enemy->_position.y - _position.y;
			sf::Vector2f speed(diffx/sqrt(diffx*diffx + diffy*diffy), diffy/sqrt(diffx * diffx + diffy * diffy));
			bullets->push_back(new Bullet(sf::Vector2f(_position.x, _position.y), sf::Vector2f(10.0f, 10.0f), speed));
		}
	}
};