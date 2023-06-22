#include "Game.h"

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space foo - Game 3", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

//Constructors Destructors
Game::Game()
{
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

void Game::pollEvents()
{
    sf::Event e;
    while(this->window->pollEvent)
}

void Game::render()
{
    
}

void Game::update()
{

}
