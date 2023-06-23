#pragma once

#include "Player.h"
 

class Game
{
private:
    //Variables
    sf::RenderWindow * window;
    sf::Event ev;

    //Player
    Player * player;

    //Private functions
    void initWindow();
    void initPlayer();

public:
    Game();
    virtual ~Game();

    void pollEvents();
    void updateInput();

    void run();
    void update();
    void render();
};