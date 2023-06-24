#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>

class Bullet
{
private:
    //Variables
    sf::Sprite shape;

    sf::Vector2f direction;
	float movementSpeed;

public:
    Bullet(sf::Texture * texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, float bullet_scale);
    ~Bullet();

	//Accessor
	const sf::FloatRect getBounds() const;

    void update();
    void render(sf::RenderTarget& target);
};