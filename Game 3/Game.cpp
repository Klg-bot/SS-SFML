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
    this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
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

void Game::updateEnemies()
{
    //Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x-20.f, -100.f));
		this->spawnTimer = 0.f;
	}

    //Update
	unsigned counter = 0;
	for (auto *enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
        
		++counter;
	}
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
    this->player->update();
    this->updateEnemies();
}

void Game::render()
{
    this->window->clear();

    //Draw game
    this->player->render(*this->window);

    for (auto *enemy : this->enemies)
	{
		enemy->render(this->window);
	}

    this->window->display();
}
