#pragma once

#include <string>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "GameWindow.hpp"

namespace hast{
class Game{
public:
	Game();
	Game(const std::string winTittle, sf::Vector2u winSize);
	~Game();

	void HandleInput();
	void Update();
	void Render();
	hast::GameWindow* GetWindow();

	void Run();

	// Clock
	sf::Time GetElapsed() { return elapsed; };
	void RestartClock() { clock.restart(); };


private:
	sf::Sprite player;
	hast::GameWindow* gamewindow;

	sf::Clock clock;
	sf::Time elapsed;

};
}
