#include "pch.h"
#include "Game.h"
#include "Vec2i.h"
#include "AStar.h"
#include "Tower.h"
#include <typeinfo>
#include <time.h>
#include "MapBuilder.h"
#include "Enemy.h"

Game::Game(const Menu& menu, const sf::RenderWindow& window, const sf::Vector2i& sizeOfMap)
	: _mainMenu(const_cast<Menu*>(&menu)),
	  _window(const_cast<sf::RenderWindow*>(&window)),
	  _sizeOfMap(sizeOfMap)
{	
	_map = nullptr;
	_state = GameWindow::MainMenu;
	_phase = Phase::Setup;
	_enemies = nullptr;
	_player = _player
		.setHealth(200)
		.setMoney(1000);
}

void Game::drawMainMenu()
{
	_mainMenu->draw(*_window);
}

void Game::drawOptionScreen()
{
	//_optionMenu->draw(*_window);
}

void Game::loadVideoGame()
{
	Tile** tile = new Tile * [_sizeOfMap.y];
	for (int i = 0; i < _sizeOfMap.y; i++)
	{
		tile[i] = new Tile[_sizeOfMap.x];
		for (int j = 0; j < _sizeOfMap.x; j++)
		{
			tile[i][j].setPosition(i * 40.0f, j * 40.0f)
				.setSize(40.0f, 40.0f)
				.setFillColor(((i + j) % 2 == 0) ? sf::Color::White : sf::Color::White);
		}
	}
	this->_map = tile;

	srand((unsigned int)time(NULL));

	sf::Vector2i start(0, rand() % _sizeOfMap.y);
	sf::Vector2i end(_sizeOfMap.x - 1, rand() % _sizeOfMap.y);

	_path = buildRoute(start, end);
}

void Game::loadBattlePhase()
{
	Entity** temp = new Entity* [10];
	for (int i = 0; i < 10; i++)
	{
		Enemy *enemy = new Enemy();
		enemy->setPosition(sf::Vector2f((float)_path[0].x * 40.0f + 15.0f - i * 40.0f, (float)_path[0].y * 40.0f + 15.0f));
		enemy->setSize(sf::Vector2f(10.0f, 10.0f));
		enemy->setSpeed(sf::Vector2f(1.0f, 0.0f));
		temp[i] = enemy;
	}
	_enemies = temp;
}

void Game::updateBattlePhase()
{
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i]->update();
		if (_bullets[i]->getToDelete())
		{
			_bullets.erase(_bullets.begin() + i);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (_enemies[i]) {
			Enemy* enemy = dynamic_cast<Enemy*>(_enemies[i]);
			enemy->update(&_path);
			if (enemy->_killed)
			{
				delete enemy;
				enemy = nullptr;
				_player._money += iteration * 20;
			}
			else if (enemy->_finished)
			{
				delete enemy;
				enemy = nullptr;
				_player._health -= iteration * 5;
			}
			_enemies[i] = enemy;
		}
	}
	
	for (int i = 0; i < _sizeOfMap.y; i++)
	{
		for (int j = 0; j < _sizeOfMap.x; j++)
		{
			if (_map[i][j]._entity)
			{
				Tower* tower = dynamic_cast<Tower*>(_map[i][j]._entity);
				if (tower)
				{
					tower->attack(_enemies, &_bullets);
				}
			}
		}
	}

	bool next = true;
	for (int i = 0; i < 10; i++)
	{
		if (_enemies[i])
		{
			next = false;
		}
	}
	if (next)
	{
		_phase = Game::Phase::Setup;
	}
}

void Game::drawVideoGame()
{
	for (int i = 0; i < _sizeOfMap.y; i++)
	{
		for (int j = 0; j < _sizeOfMap.x; j++)
		{
			_map[i][j].draw(*_window);
		}
	}

	if (_phase == Game::Phase::Battle) {
		for (int i = 0; i < 10; i++)
		{
			if (_enemies[i])
			{
				_enemies[i]->draw(*_window);
			}
		}
		for (int i = 0; i < _bullets.size(); i++)
		{
			if (_bullets[i])
			{
				_bullets[i]->draw(*_window);
			}
		}
	}
}

bool Game::handleEvents()
{
	sf::Event event;

	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_window->close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) 
			{
			case sf::Keyboard::W:
				if (_state == Game::GameWindow::MainMenu)
				{
					_mainMenu->move(true);
				}
				break;
			case sf::Keyboard::S:
				if (_state == Game::GameWindow::MainMenu)
				{
					_mainMenu->move(false);
				}
				break;
			case sf::Keyboard::Return:
				if (_state == Game::GameWindow::MainMenu) {
					int option = _mainMenu->getSelected();
					switch (option)
					{
					case 0:
						if (_state == Game::GameWindow::MainMenu)
						{
							loadVideoGame();
							_state = Game::GameWindow::VideoGame;
						}
						break;

					case 1:
						if (_state == Game::GameWindow::MainMenu)
						{
							loadVideoGame();
							_state = Game::GameWindow::VideoGame;
						}
						break;

					case 2:
						if (_state == Game::GameWindow::MainMenu)
						{
							_state = Game::GameWindow::OptionScreen;
						}
						break;

					case 3:
						if (_state == Game::GameWindow::MainMenu)
						{
							_window->close();
							return EXIT_SUCCESS;
						}
						break;
					}
					break;
				} 
				else if (_state == Game::GameWindow::VideoGame)
				{
					_phase = Game::Phase::Battle;
					loadBattlePhase();
					drawVideoGame();
				}
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left && _phase == Game::Phase::Setup)
			{
				if (_state == Game::GameWindow::VideoGame) 
				{
					sf::Vector2i position = sf::Mouse::getPosition();
					position.x -= 649;
					position.y -= 259;
					std::cout << position.x << " " << position.y << std::endl;

					Tile** tempMap = _map;

					for (int i = 0; i < _sizeOfMap.y; i++)
					{
						for (int j = 0; j < _sizeOfMap.x; j++)
						{
							Tile tempTile = tempMap[j][i];
							sf::RectangleShape rect;
							rect.setPosition(*(tempTile._position));
							rect.setSize(*(tempTile._size));
							if (rect.getGlobalBounds().contains(_window->mapPixelToCoords(position)))
							{
								std::cout << tempTile._position->x << " " << tempTile._position->y << std::endl;
								if (!tempTile._entity) {
									if (_player._money >= 100) {
										Tower tower;
										tower.setPosition((int)tempTile._position->x, (int)tempTile._position->y)
											.setTexture("./tower.png");
										tempMap[j][i] = tempTile.setEntity(tower);
										this->drawVideoGame();
										_player._money -= 100;
									}
									else {
										std::cout << "You dont have enough money to place a Tower here!!" << std::endl;
									}
								}
								else {
									std::cout << "You cant place a Tower on an already taken tile!" << std::endl;
								}
							} 
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}
}

bool Game::runs()
{
	return _window->isOpen();
}

void Game::draw()
{
	_window->clear();
	switch (_state)
	{
	case Game::GameWindow::MainMenu:
		this->drawMainMenu();
		break;
	case Game::GameWindow::VideoGame:
		this->drawVideoGame();
		if (_phase == Game::Phase::Battle) {
			this->updateBattlePhase();
		}
		break;
	case Game::GameWindow::OptionScreen:
		this->drawOptionScreen();
		break;	
	}
	_window->display();
}

std::vector<sf::Vector2i> Game::findPath(sf::Vector2i& start, sf::Vector2i& end)
{
	auto path = _astar.findPath(start, end, pf::heuristic::euclidean, 1);
	return path;
}

Game::~Game()
{
	/*delete _menu;
	delete _window;*/
}

std::vector<sf::Vector2i> Game::buildRoute(const sf::Vector2i& start, const sf::Vector2i& end)
{
	mb::MapBuilder *mapBuilder = new mb::MapBuilder(start, end, _sizeOfMap);
	return mapBuilder->build(this->_map);
}