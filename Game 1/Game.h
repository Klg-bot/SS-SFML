#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/* 
Class that acts as game engine
*/

class Game
{
private:
    ////Variables////

    //Window
    sf::RenderWindow* window; 
    sf::VideoMode videoMode;
    sf::Event ev;

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    sf::Font font;

    //Texts
    sf::Text uiText;

    //Game logic
    bool endGame;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    int enemyType;
    bool mouseHeld;
    int health;

    //Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //Private functions 
    void initVariables();
    void initWindows();
    void initEnemies();
    void initFonts();
    void initText();

public:
    //Constructors / Destructorsm
    Game();
    virtual ~Game();

    //Accessors
    const bool running() const;
    const bool getEndGame() const;


    //Functions 
    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();

};