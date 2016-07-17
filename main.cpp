#include <iostream>
#include <limits>

#include "RandomGenerator.hpp"
#include "Game.hpp"

int main()
{
    // Initializing random seed.
    RandomGenerator::initSeed();

    // Initializing a game instance.
    Game g;

    // Calling the main menu (input prompt loop).
    g.prompt();

    // Freezing the screen.
    std::cin.get();

    return 0;
}
