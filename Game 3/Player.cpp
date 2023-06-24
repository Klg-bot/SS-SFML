#include "Player.h"

void Player::initVariables()
{
    this->movementSpeed = 2.f;

    this->hpMax = 100;
	this->hp = this->hpMax;

}

void Player::initSprite()
{
    //Set the texture to the sprite
	this->sprite.setTexture(this->texture);
    sprite.setPosition(400, 300);

	//Resize the sprite
	this->sprite.scale(0.1f, 0.1f);
}

void Player::initTexture()
{
    if(!this->texture.loadFromFile("Images/ship.png"))
    {
        std::cout << "Couldn't load textures!" << std::endl;
    }
}

//Const Dest
Player::Player()
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
}

Player::~Player()
{
}

sf::Vector2f Player::getPos()
{
    return this->sprite.getPosition();
}

sf::FloatRect Player::getBounds()
{
    return this->sprite.getGlobalBounds();
}

void Player::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Player::update()
{
    
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

