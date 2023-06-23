#include "Game.h"

Game::Game()
{
    this->window = new sf::RenderWindow(sf::VideoMode(200, 200),"SFML works!", sf::Style::Close);
    this->shape = sf::CircleShape(100.f);
    this->shape.setFillColor(sf::Color::Green);
}

Game::~Game()
{
    delete this->window;
}

void Game::run()
{
    while (this->window->isOpen())
    {
        sf::Event event;
        while (this->window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window->close();
        }

        this->window->clear();
        this->window->draw(this->shape);
        this->window->display();
    }
}
