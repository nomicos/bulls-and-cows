#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <utility>
#include <string>

#include "RandomGenerator.hpp"
#include "Number.hpp"

class Game
{
private:
    int number;
    int guess_counter;

    static const std::string intro;

public:
    Game();

    int getGuessCounter() const;
    std::pair<int,int> guess(const int & g);
};

#endif // GAME_H_INCLUDED
