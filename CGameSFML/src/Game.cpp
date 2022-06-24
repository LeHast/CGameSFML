#include "Game.hpp"


hast::Game::Game(){
	gamewindow = new GameWindow();
	Run();
}


hast::Game::Game(const std::string winTittle, sf::Vector2u winSize) {
	gamewindow = new GameWindow(winTittle, winSize);
	Run();
}


hast::Game::~Game(){
	//gamewindow->~GameWindow();
	std::cout << "Game Destroyed \n";
	delete gamewindow;
}


void hast::Game::Run(){
	

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/player.png"))
		std::cout << "Texture Not Found! \n";
	else
		std::cout << "Texture Found! \n";
	player.setTexture(playerTexture);

	sf::Vector2u size = playerTexture.getSize();
	player.setOrigin(size.x / 2, size.y / 2);
	player.setPosition(1200 / 2, 880 / 2);
	player.setColor(sf::Color::Blue);


	while (!gamewindow->IsDone()) {
		HandleInput();
		Update();
		Render();
	}
}

void hast::Game::HandleInput(){
}

void hast::Game::Update(){
	gamewindow->Update();
}

void hast::Game::Render(){
	gamewindow->BeginDraw();
	gamewindow->Draw(player);
	gamewindow->EndDraw();
}

hast::GameWindow* hast::Game::GetWindow() {
	return gamewindow;
}


