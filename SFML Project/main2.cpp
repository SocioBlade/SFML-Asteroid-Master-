#include <SFML\Graphics.hpp>
#include "Const.hpp"
#include <crtdbg.h>
#include "Game.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Asteroids");
	window.setFramerateLimit(60);
	Game game;
	sf::Clock clock;


	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
		}
		
		game.gameUpdate(clock.restart().asSeconds());

		window.clear(sf::Color::Black);
		window.draw(game);
		window.display();
		
	}

	//system("Pause");
	return 0;
}