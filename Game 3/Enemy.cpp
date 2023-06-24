#include "Enemy.h"

void Enemy::initVariables()
{
    // this->pointCount = rand() % 8 + 3; //min = 3 max = 10
	// this->type		= 0;
	// this->speed		= static_cast<float>(this->pointCount/3);
	// this->hpMax		= static_cast<int>(this->pointCount);
	// this->hp		= this->hpMax;
	// this->damage	= this->pointCount;
	// this->points	= this->pointCount;
}

void Enemy::initShape() //
{
    this->shape.setRadius(10);
	this->shape.setFillColor(sf::Color::Green);
    this->shape.setPosition(300, 300);
}

Enemy::Enemy() //
{
	this->initVariables();
	this->initShape();
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
    // this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget *target) //
{
    target->draw(this->shape);
}
