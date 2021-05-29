#pragma once
#include <SFML/Graphics.hpp>
#include "MenuButton.h"

class Menu
{
public:
	Menu();
	Menu(const Menu&);
	Menu& operator=(const Menu&);
	void renderOptions();
	~Menu();
public:
	void draw(sf::RenderWindow&) const;
	void move(const bool&); //1 = up, 0 = down
	Menu& setResolution(const sf::Vector2u&);
	Menu& loadFont(const std::string&);
	Menu& setContents(const std::string&, const int&);
	Menu& loadButtons();
	int getSelected() const;
	Menu& create();
	Menu& loadContents(const std::string&);
private:
	int _selected;
	int _length;
	sf::Font* _font;
	MenuButton* _menuButton;
	std::string _contents;
	sf::Vector2u* _resolution;
};