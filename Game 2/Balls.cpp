#include "Balls.h"

void Balls::initShape(const sf::RenderWindow& window)
{
	this->shape.setRadius(static_cast<float>(rand() % 15 + 10));

	sf::Color color;
	switch (this->type)
	{
	case DEFAULT:
		color = sf::Color::Blue;
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(5.f);
		break;
	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(5.f);
		break;

	}
	this->shape.setFillColor(color);
	this->shape.setPosition(
		sf::Vector2f(
			std::abs(static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width)),
			std::abs(static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height))
		)
	);
}

//Constructors Destructors
Balls::Balls(const sf::RenderWindow& window, int type)
	:type(type)
{
	this->initShape(window);
}

Balls::~Balls()
{

}

const sf::CircleShape Balls::getShape() const
{
	return this->shape;
}

const int& Balls::getType() const
{
	return this->type;
}

//Update Render
void Balls::update()
{

}

void Balls::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
