#include "pch.h"
#include "Menu.h"
#include "Game.h"
#include "ArgumentException.h"

//czy jest sens explicitly includowac
//naglowki, ktore zawieraja sie w innych naglowkach

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "Tower Defence");
	
	Menu menu;
	menu.create();
	Game game(menu, window, sf::Vector2i(16,16));

	while (game.runs())
	{
		game.handleEvents();
		game.draw();

		if (!game.checkPlayer())
		{
			return EXIT_SUCCESS;
		}
	}
}