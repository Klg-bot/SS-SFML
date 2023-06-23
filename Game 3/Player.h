#pragma once

#include <iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Player
{
private:
    //Variables
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;

    int hp;
    int hpMax;

    //Private functions
    void initVariables();
    void initSprite();
    void initTexture();
    
public:
    Player();
    ~Player();

    void move(const float dirX, const float dirY);

    void update();
    void render(sf::RenderTarget& target);
};