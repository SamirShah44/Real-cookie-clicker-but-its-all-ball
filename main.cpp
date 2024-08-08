#include "Game.h"
int main()
{
    //Init srand
    srand(static_cast<unsigned>(time(0)));

    //Init Game window
    Game game;

    while (game.running())
    {
       //Update
        game.update();
       //Render
        game.render();
       //

    }

    return 0;
}
