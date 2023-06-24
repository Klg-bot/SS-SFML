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
    //Const Dest
    Player();
    ~Player();

    //Accessors
    sf::Vector2f getPos();
    sf::FloatRect getBounds();
    int getHp();
    int getHpMax();


    //Functions

    void takeDamage(const int damage);
    void gainHealth(const int healing);

    void move(const float dirX, const float dirY);
    void setPosition(const float x, const float y);

    void update();
    void render(sf::RenderTarget& target);
};