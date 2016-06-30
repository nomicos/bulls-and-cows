#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <utility>

#include "Random.h"
#include "Number.h"

class Game
{
private:
    int number;
    int guess_counter;

public:
    Game();

    int getGuessCounter() const;
    std::pair<int,int> guess(const int & g);
};

#endif // GAME_H_INCLUDED
