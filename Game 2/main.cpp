#include "Game.h"

int main()
{
    //Initialise random seed
    srand(static_cast<unsigned>(NULL));

    //Initialise game object
    Game game;

    //Game loop
    while(game.running())
    {
        game.update();
        game.render();
    }

    //End of application 
    return 0;
}