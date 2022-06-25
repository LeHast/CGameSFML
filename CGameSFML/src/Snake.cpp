#include "Snake.h"

Snake::Snake(int initialSize) :score{0} {
	size = initialSize;
	bodyRect.setSize(sf::Vector2f(size - 1, size - 1));
	Reset();
}

Snake::~Snake(){
}

void Snake::SetDirection(Direction todir){
	dir = todir;
}

Direction Snake::GetDirection(){
	return dir;
}

int Snake::GetSpeed(){
	return speed;
}

sf::Vector2i Snake::GetPosition(){
	return (!snakeBody.empty() ? snakeBody.front().position : sf::Vector2i(1,1));
}

int Snake::GetLives(){
	return lives;
}

int Snake::GetScore(){
	return score;
}

void Snake::IncreaseScore(){
	score += 10;
}

bool Snake::HasLost()
{
	return lost;
}

void Snake::Lose(){
	lost = true;
}

void Snake::ToggleLost(){
	lost = !lost;
}

void Snake::Extend(){
	if (snakeBody.empty()) {
		return;
	}
	
	SnakeSegment& tail_head = snakeBody[snakeBody.size() - 1];

	if (snakeBody.size() > 1) {
		SnakeSegment& tail_bone = snakeBody[snakeBody.size() - 2];
	
		if (tail_head.position.x == tail_bone.position.x) {
			if (tail_head.position.y > tail_bone.position.y) {
				snakeBody.push_back(SnakeSegment(
					tail_head.position.x, tail_head.position.y + 1));
			}
			else {
				snakeBody.push_back(SnakeSegment(
					tail_head.position.x, tail_head.position.y - 1));
			}
		}
		else if (tail_head.position.y == tail_bone.position.y) {
			if (tail_head.position.x > tail_bone.position.x) {
				snakeBody.push_back(SnakeSegment(
					tail_head.position.x + 1, tail_head.position.y));
			}
			else {
				snakeBody.push_back(SnakeSegment(
					tail_head.position.x - 1, tail_head.position.y));
			}
		}
	}
	else {
		if (dir == Direction::Up) {
			snakeBody.push_back(SnakeSegment(
				tail_head.position.x, tail_head.position.y + 1));
		}
		else if (dir == Direction::Down) {
			snakeBody.push_back(SnakeSegment(
				tail_head.position.x, tail_head.position.y - 1));
		}
		else if (dir == Direction::Left) {
			snakeBody.push_back(SnakeSegment(
				tail_head.position.x + 1, tail_head.position.y));
		}
		else if (dir == Direction::Right) {
			snakeBody.push_back(SnakeSegment(
				tail_head.position.x - 1, tail_head.position.y));
		}
	} 

}

void Snake::Reset(){
	snakeBody.clear();

	for (size_t i = 5; i < 8; i++){
		snakeBody.push_back(SnakeSegment(5, i));
	}
	
	SetDirection(Direction::None);
	speed = 15;
	lives = 3;
	score = 0;
	lost = false;

}

void Snake::Move(){

	for (int i = snakeBody.size() - 1; i > 0; --i) {
		snakeBody[i].position = snakeBody[i - 1].position;
	}
	if (dir == Direction::Left) {
		--snakeBody[0].position.x;
	}
	else if (dir == Direction::Right) {
		++snakeBody[0].position.x;
	}
	else if (dir == Direction::Up) {
		--snakeBody[0].position.y;
	}
	else if (dir == Direction::Down) {
		++snakeBody[0].position.y;
	}


}


void Snake::Tick(){
	if (snakeBody.empty()) {
		return;
	}
	if (dir == Direction::None) {
		return;
	}
	Move();
	CheckCollision();
}

void Snake::Cut(int l_segments){
	for (int i = 0; i < l_segments; ++i) {
		snakeBody.pop_back();
	}
	--lives;
	if (!lives) 
		Lose();
	return; 
}


void Snake::Render(sf::RenderWindow& l_window){
	if (snakeBody.empty()) {
		return;
	}
	auto head = snakeBody.begin();

	bodyRect.setFillColor(sf::Color::Yellow);

	bodyRect.setPosition(head->position.x * size, head->position.y * size);
	l_window.draw(bodyRect);
	bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = snakeBody.begin() + 1;
		itr != snakeBody.end(); ++itr)
	{
		bodyRect.setPosition(itr->position.x * size,
			itr->position.y * size);
		l_window.draw(bodyRect);
	}
}

void Snake::CheckCollision(){
	if (snakeBody.size() < 5) { 
		return;
	}
	SnakeSegment& head = snakeBody.front();
	for (auto itr = snakeBody.begin() + 1; itr != snakeBody.end(); ++itr){
		if (itr->position == head.position) {
			int segments = snakeBody.end() - itr;
			Cut(segments);
			break;
		}
	}
}
