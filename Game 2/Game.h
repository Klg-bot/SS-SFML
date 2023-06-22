#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

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

    int points;

    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    std::vector<Balls> balls;
    float spawnTimerMax;
    float spawnTimer;
    int maxBalls;


    void initVariable();
    void initWindow();
    void initFonts();
    void initText();
    
public:
    //Constructors & Destructors
    Game();
    ~Game();

    //Accesors
    const bool getEndGame() const;

    //Modifiers

    //Functions 
    const bool running() const;
    void pollEvents();

    const int randBallType() const;
    void spawnBalls();
    void updatePlayer();
    void updateCollision();
    void updateGui();
    void update();

    void renderGui(sf::RenderTarget* target);
    void render();

    

};