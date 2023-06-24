#pragma once

#include "Player.h"
#include "Enemy.h"

#include <ctime>
 

class Game
{
private:
    //Variables
    sf::RenderWindow * window;
    sf::Event ev;

    //Player
    Player * player;
    
    Enemy * enemy;

    //Private functions
    void initWindow();

    void initPlayer();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    void pollEvents();
    void updateInput();

    void run();
    void update();
    void render();
};