#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Game
{
private:
    //Variables
    sf::RenderWindow * window;
    sf::CircleShape shape;

public:
    Game();
    ~Game();

    void run();
};
