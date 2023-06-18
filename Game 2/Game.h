#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include "Player.h"

class Game
{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    bool endGame;
    sf::Event sfmlEvent;

    Player player;

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

    void update();
    void render();

};