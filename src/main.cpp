#include <iostream>

#include <SFML/Graphics.hpp>
#include "../extern/box2d/include/box2d/box2d.h"

#include "TetrisLogic/Tetris.hpp"
#include "TetrisVisual/TetrisView.hpp"
#include "TetrisVisual/MenuView.hpp"
#include "InputController.hpp"

#include "States/MenuState.hpp"
#include "TetrisLogic/Rules/StandartRules.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16u;

	sf::RenderWindow window(sf::VideoMode(600, 800), "Physical Tetris | v0.6 alpha", sf::Style::Close, settings);
	pt::Tetris tetris(3.f);
	pt::TetrisView view(window, tetris, 10.f);
	pt::MenuView menu(window);
	pt::InputController controller(tetris, view, menu);

	window.setKeyRepeatEnabled(true);
	window.setFramerateLimit(60);

	tetris.setRules(new pt::StandartRules(&tetris));
	controller.setState(new pt::MenuState(&controller));

	srand(time(0));
	sf::Clock worldClock;
	sf::Clock spawnClock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			controller.checkEvent(event);
		}

		controller.update(worldClock.restart().asSeconds());
		
		if (spawnClock.getElapsedTime().asSeconds() > 5.f)
		{
			spawnClock.restart();
		}

		window.clear(sf::Color::Black);
		controller.draw();
		window.display();
	}

	return 0;
}