#include <iostream>
#include "Game.h"

int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Initialize game engine
    Game game;

    //Game loop
    while(game.running() && !game.getEndGame())
    {
        //Update 
        game.update();

        //Render
        game.render();
    }

    //End of application
    return 0;
}