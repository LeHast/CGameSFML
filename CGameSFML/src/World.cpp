#include "World.hpp"

World::World(sf::Vector2u l_windSize){
    blockSize = 16;
    windowSize = l_windSize;
    RespawnApple();
    appleShape.setFillColor(sf::Color::Red);
    appleShape.setRadius(blockSize / 2);
    for (int i = 0; i < 4; ++i) {
        bounds[i].setFillColor(sf::Color(150, 0, 0));
        if (!((i + 1) % 2)) {
            bounds[i].setSize(sf::Vector2f(windowSize.x,blockSize));
        }
        else {
            bounds[i].setSize(sf::Vector2f(blockSize,windowSize.y));
        }
        if (i < 2) {
            bounds[i].setPosition(0, 0);
        }
        else {
            bounds[i].setOrigin(bounds[i].getSize());
            bounds[i].setPosition(sf::Vector2f(windowSize));
        }
    }

}

World::~World(){
}

int World::GetBlockSize(){
    return blockSize;
}

void World::RespawnApple(){
    int maxX = (windowSize.x / blockSize) - 2;
    int maxY = (windowSize.y / blockSize) - 2;
    item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
    appleShape.setPosition(item.x * blockSize, item.y * blockSize);
}

void World::Update(Snake& l_player){
    if (l_player.GetPosition() == item) {
        l_player.Extend();
        l_player.IncreaseScore();
        RespawnApple();
    }
    int gridSize_x = windowSize.x / blockSize;
    int gridSize_y = windowSize.y / blockSize;
    if (l_player.GetPosition().x <= 0 || l_player.GetPosition().y <= 0 || l_player.GetPosition().x >= gridSize_x - 1 || 
        l_player.GetPosition().y >= gridSize_y - 1){
        l_player.Lose();
    }
}

void World::Render(sf::RenderWindow& l_window){
    for (int i = 0; i < 4; ++i) {
        l_window.draw(bounds[i]);
    }
    l_window.draw(appleShape);

}
