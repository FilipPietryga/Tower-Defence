#pragma once
#include "Menu.h"
#include "Tile.h"
#include "Vec2i.h"
#include "AStar.h"
#include "MapBuilder.h"
#include "Player.h"
#include "vector"
#include "Bullet.h"

class Game
{
public:
	Game(const Menu&, const sf::RenderWindow&, const sf::Vector2i&);
	~Game();
public:
	void drawMainMenu();
	void drawVideoGame();
	void drawOptionScreen();
	void loadVideoGame();
	void initializeMap(int x, int y);
	std::vector<sf::Vector2i> buildRoute(const sf::Vector2i& start, const sf::Vector2i& end);
	void draw();
	std::vector<sf::Vector2i> findPath(sf::Vector2i& start, sf::Vector2i& end);
	bool runs();
	bool checkPlayer()
	{
		return _player._health > 0 ? true : false;
	}
	void loadBattlePhase();
	void updateBattlePhase();
public:
	bool handleEvents();
	void render();
private:
	Menu* _mainMenu;
	Tile** _map;
	Entity** _enemies;
	sf::RenderWindow* _window;
	enum class GameWindow : char { MainMenu, VideoGame, OptionScreen }; 
	enum class Phase : char { Setup, Battle }; 
	Phase _phase;
	GameWindow _state;	
	pf::AStar _astar;
	sf::Vector2i _sizeOfMap;
	std::vector<sf::Vector2i> _path;
	Player _player;
	int iteration = 1;
	std::vector<Bullet*> _bullets;
};