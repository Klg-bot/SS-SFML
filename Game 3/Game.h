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

    //Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

    //Private functions
    void initWindow();

    void initPlayer();
    void initEnemies();

public:
    //Const Dest
    Game();
    virtual ~Game();

    //Functions

    void pollEvents();
    void updateInput();
    void updateEnemies();


    void update();
    void render();

    void run();
};