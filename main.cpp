#include <iostream>

#include "RandomGenerator.hpp"
#include "Number.hpp"
#include "Game.hpp"
#include "Menu.hpp"

int main()
{
    // Initializing random seed.
    RandomGenerator::initSeed();

    // Initializing a game instance.
    Game g;

    // Entering menu for that game.
    Menu::ask(g);

    // Freeze the screen; dunno why one cin.get() doesn't work.
    std::cin.get();
    std::cin.get();

    return 0;
}
