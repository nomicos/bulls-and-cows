#include "Game.h"

Game::Game()
{
    this->guess_counter = 0;

    do
    {
        this->number = ( Random::get() % (9999 - 1000) ) + 1000;
    } while(!Number::correct(this->number));

    std::cout << "A 4-digit number has been chosen. Try to guess." <<
                 "\n>>> DEBUG: " << this->number << std::endl;
}

int Game::getGuessCounter() const
{
    return this->guess_counter;
}

std::pair<int,int> Game::guess(const int & g)
{
    // Function returning a pair of values:
    //   first - bulls (position hit)
    //   second - cows (no position hit)

    // 1000 <= g <= 9999

    int a = this->number;
    int b = g;
    int bulls = 0, cows = 0;

    while(a)
    {
        if(a % 10 == b % 10)
        {
            bulls++;
        }
        else
        {
            int t = this->number;
            while(t)
            {
                if(t % 10 == b)
                {
                    cows++;
                    break;
                }

                t /= 10;
            }
        }

        a /= 10;
        b /= 10;
    }

    this->guess_counter++;
    return std::make_pair(bulls, cows);
}
