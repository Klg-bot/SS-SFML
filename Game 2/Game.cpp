#include "Game.h"


void Game::initVariable()
{
    this->endGame = false;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(1200, 1000);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
}

// Constructors & Destructors
Game::Game()
{
    this->initVariable();
    this->initWindow(); 
}

Game::~Game()
{
    delete this->window;
}

// Functions
const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->sfmlEvent))
    {
        switch (this->sfmlEvent.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        
        case sf::Event::KeyPressed:
            if(this->sfmlEvent.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
            break;
        }
    }
}

void Game::update()
{
    this->pollEvents();
}

void Game::render()
{
    this->window->clear();

    //Draw game
    this->player.render(this->window);

    this->window->display();
}
