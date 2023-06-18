#include "Game.h"


void Game::initVariable()
{
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = this->spawnTimerMax;
    this->maxBalls = 10;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);

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

void Game::spawnBalls()
{
    //Timer
    if (this->spawnTimer < this->spawnTimerMax)
    {
        this->spawnTimer += 1.f;
    }
    else
    {
        if (this->balls.size() < this->maxBalls)
        {
            this->balls.push_back(Balls(*this->window));

            this->spawnTimer = 0.f;
        }
    }
}

void Game::updateCollision()
{
    //Check the collision

    for (auto i : this->balls)
    {
        if(this->player.getShape().getGlobalBounds().intersects(i.get)
    }
    //Im trying my own for loop
    //TODO: add getShapes for Balls class

}

void Game::update()
{
    this->pollEvents();

    this->player.update(this->window);

    this->spawnBalls();

    //Output testing

    /*std::cout << rand() % this->window->getSize().x << std::endl;*/

    sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);
    std::cout << "Mouse X: " << mousePosition.x << ", Mouse Y: " << mousePosition.y << std::endl;
}

void Game::render()
{
    this->window->clear();

    //Draw game
    this->player.render(this->window);

    for (auto i : this->balls)
    {
        i.render(*this->window);
    }

    this->window->display();
}
