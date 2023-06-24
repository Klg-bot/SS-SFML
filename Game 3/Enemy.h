#pragma once

#include<SFML/Graphics.hpp>

class Enemy
{
private:
    //Variables
    sf::CircleShape shape;

    unsigned pointCount;
    int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

    void initVariables();
    void initShape();
    
public:
    //Const Dest
    Enemy();
    ~Enemy();


    void update();
    void render(sf::RenderTarget* target);
};