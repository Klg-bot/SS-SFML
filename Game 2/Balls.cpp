#include "Balls.h"

void Balls::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	sf::Color colour(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	this->shape.setFillColor(colour);
	this->shape.setPosition(
		sf::Vector2f(
			std::abs(static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width)),
			std::abs(static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height))
		)
	);
}

//Constructors Destructors
Balls::Balls(const sf::RenderWindow& window)
{
	this->initShape(window);
}

Balls::~Balls()
{

}

//Update Render
void Balls::update()
{

}

void Balls::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
