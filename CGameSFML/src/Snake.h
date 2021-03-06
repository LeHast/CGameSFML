#pragma once

#include "SFML/Graphics.hpp"
#include <vector>

enum class Direction{
	Up,
	Down,
	Left,
	Right,
	None,

	Default
};

struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

class Snake{
public:
	Snake(int l_blockSize);
	~Snake();
	// Helper methods.
	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();
	void Lose(); // Handle losing here.
	void ToggleLost();
	void Extend(); // Grow the snake.
	void Reset(); // Reset to starting position.
	void Move(); // Movement method.
	void Tick(); // Update method.
	void Cut(int l_segments); // Method for cutting snake.
	void Render(sf::RenderWindow& l_window);
private:
	void CheckCollision(); // Checking for collisions.
	SnakeContainer snakeBody; // Segment vector.
	int size; // Size of the graphics.
	Direction dir; // Current direction.
	int speed; // Speed of the snake.
	int lives; // Lives.
	int score; // Score.
	bool lost; // Losing state.
	sf::RectangleShape bodyRect; // Shape used in rendering.

};

