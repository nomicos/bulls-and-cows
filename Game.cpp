#include "Game.h"

Game::Game()
{
    do
    {
        this->number = ( Random::get() % (9999 - 1000) ) + 1000;
    } while(!Number::correct(this->number));

    std::cout << "A number has been chosen: " << this->number << std::endl;
}

std::pair<int,int> Game::guess(const int & g) const
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

    return std::make_pair(bulls, cows);
}
