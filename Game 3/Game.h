#pragma once

#include <iostream>
#include <sstream>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#include <ctime>
 

class Game
{
private:
    //Variables
    //Window
    sf::RenderWindow * window;
    sf::Event ev;

    //Fonts
    sf::Font font;
	sf::Text pointText;

    //Textures
    std::map<std::string, sf::Texture*> textures;

    //Player
    Player * player;

    //Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

    //Bullets
    std::vector<Bullet*> bullets;

    //Private functions
    void initWindow();

    void initPlayer();
    void initEnemies();

    void initTextures();
    void initGUI();

public:
    //Const Dest
    Game();
    virtual ~Game();

    //Functions
    void pollEvents();
    void updateInput();
    void updateEnemies();
    void updateBullets();
    void updateBounds();
    void updateCombat();

    void updateGUI();
    void renderGUI();


    void update();
    void render();

    void run();
};