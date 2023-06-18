#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "Player.h"
#include "Balls.h"

class Game
{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    bool endGame;
    sf::Event sfmlEvent;

    Player player;

    std::vector<Balls> balls;
    float spawnTimerMax;
    float spawnTimer;
    int maxBalls;

    void initVariable();
    void initWindow();
    
public:
    //Constructors & Destructors
    Game();
    ~Game();

    //Accesors

    //Modifiers

    //Functions 
    const bool running() const;
    void pollEvents();

    void spawnBalls();
    void updateCollision();
    void update();
    void render();

};