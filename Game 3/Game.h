#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Game
{
private:

    //Window
    sf::RenderWindow * window;

    //Private Functions
    void initWindow();

public:
    //Constructors Destructors
    Game();
    ~Game();

    void pollEvents();

    //Update render
    void render();
    void update();  
    
};