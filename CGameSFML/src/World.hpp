#pragma once

#include "SFML/Graphics.hpp"
#include "Snake.h"

class World{

public:
	World(sf::Vector2u l_windSize);
	~World();
	int GetBlockSize();
	void RespawnApple();
	void Update(Snake& l_player);
	void Render(sf::RenderWindow& l_window);
private:
	sf::Vector2u windowSize;
	sf::Vector2i item;
	int blockSize;
	sf::CircleShape appleShape;
	sf::RectangleShape bounds[4];

};

