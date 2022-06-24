#include "GameWindow.hpp"

hast::GameWindow::GameWindow(){
	Setup("Window", sf::Vector2u(640, 480));
}


hast::GameWindow::GameWindow(const std::string& winTittle, const sf::Vector2u& winSize){
	Setup(winTittle, winSize);
}


hast::GameWindow::~GameWindow(){
	std::cout << "GameWindow Destroyed \n";
	Destroy();
}


void hast::GameWindow::BeginDraw(){
	window.clear(sf::Color::Black);
}


void hast::GameWindow::EndDraw(){
	window.display();
}


void hast::GameWindow::Update(){
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
			ToggleFullscreen();
		
	}
}


bool hast::GameWindow::IsDone(){
	return isDone;
}


bool hast::GameWindow::IsFullscreen(){
	return fullscreen;
}


sf::Vector2u hast::GameWindow::GetWindowSize(){
	return windowSize;
}


void hast::GameWindow::ToggleFullscreen(){
	fullscreen = !fullscreen;
	Destroy();
	Create();
}


void hast::GameWindow::Draw(sf::Drawable& toDraw){
	window.draw(toDraw);
}

void hast::GameWindow::SetFPS(const int fps){
	window.setFramerateLimit(fps);
}


void hast::GameWindow::Setup(const std::string& winTittle, const sf::Vector2u& winSize){
	window.setFramerateLimit(60);
	windowTitle = winTittle;
	windowSize = winSize;
	fullscreen = false;
	isDone = false;
	Create();
}


void hast::GameWindow::Destroy(){
	window.close();
}


void hast::GameWindow::Create() {
	auto fullScreen = (fullscreen ? sf::Style::Fullscreen : sf::Style::Default);

	window.create({windowSize.x, windowSize.y, 32}, windowTitle, fullScreen);
}
