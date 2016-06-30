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

public:
    Game();

    std::pair<int,int> guess(const int & g) const;
};

#endif // GAME_H_INCLUDED
