#include <iostream>

#include "Random.h"
#include "Number.h"
#include "Game.h"
#include "Menu.h"

int main()
{
    // Initializing random seed.
    Random::init();

    // Initializing a game instance.
    Game g;

    // Entering menu for that game.
    Menu::ask(g);

    // Freeze the screen; dunno why one cin.get() doesn't work.
    std::cin.get();
    std::cin.get();

    return 0;
}
