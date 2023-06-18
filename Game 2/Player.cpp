#include "Player.h"

void Player::initVariables()
{
}

void Player::initShape()
{
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(100.f, 100.f));
}   

// Constructors Destructors
Player::Player()
{
    this->initShape();
    this->initVariables();
}

Player::~Player()
{
}


//Update and Render
void Player::update()
{

}

void Player::render(sf::RenderTarget * target)
{
    target->draw(this->shape);
}
