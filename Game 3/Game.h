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

    //Points
    int points;

    //GUI
    sf::Font font;
	sf::Text bulletVector;
	sf::Text mousePos;
	sf::Text getHp;
	sf::Text myPointsText;
    sf::RectangleShape hpBarFront;
    sf::RectangleShape hpBarBack;

    //Background
    sf::Sprite worldBackground;
    sf::Texture worldBackgroundTex;

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

    void initBackground();


public:
    //Const Dest
    Game();
    virtual ~Game();

    //Accessors
    int getPoints();

    //Functions
    void pollEvents();
    void updateInput();
    void updateEnemies();
    void updateBullets();
    void updateBounds();
    void updateCombat();

    void updateGUI();
    void renderGUI();
    void renderWorld();


    void update();
    void render();

    void run();
};