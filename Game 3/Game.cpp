#include "Game.h"

//Initialize 
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game 3", sf::Style::Fullscreen | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
    this->enemy = new Enemy();
}

//Const Dest
Game::Game()
{
    this->initWindow();
    this->initPlayer();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
    delete this->player;
    delete this->enemy;
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        if (this->ev.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::updateInput()
{
    //Move player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->player->move(-1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->player->move(1.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->player->move(0.f, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->player->move(0.f, 1.f);
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->pollEvents();

		this->update();

		this->render();
	}
}

//Update render
void Game::update()
{
    this->updateInput();
}

void Game::render()
{
    this->window->clear();

    //Draw game
    this->player->render(*this->window);
    this->enemy->render(this->window);

    this->window->display();
}
