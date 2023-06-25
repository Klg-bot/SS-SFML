#include "Game.h"

int main()
{
    //Initialise random seed
    srand(static_cast<unsigned>(time(NULL)));

    //Initialise game object
    Game game;

    //Game loop
    while (game.running())
    {
        if(!game.getEndGame())
            game.update();  
            
        game.render();
    }

    //End of application 
    return 0;
}