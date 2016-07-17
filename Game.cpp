#include <iostream>

#include "Game.hpp"

const std::string Game::intro =
    "Welcome to the BULLS AND COWS game!\n\n"
    "The computer has just chosen a random 4-digit number. Your task\n"
    "is to guess the number using as few attempts as possible. Each\n"
    "time you make a guess, the computer will give you two hint numbers:\n"
    "'bulls' and 'cows' which represent how many digits your number\n"
    "and the number chosen by the computer have in common. Moreover,\n"
    "if you guessed not only a digit but its position as well, that\n"
    "would make a 'bull'; if you got the digit right but it is actually\n"
    "in a position different than you suggested, that counts as a 'cow'.\n"
    "\nNote that the chosen number is always composed of four digits\n"
	"each one of which is different from the others. The first digit is\n"
	"different from zero. All invalid guessed will be discarded.\n"
    "\nPlease refer to the Wikipedia article for more details:\n"
    "https://en.wikipedia.org/wiki/Bulls_and_cows\n\n";

Game::Game()
{
    this->guess_counter = 0;

    do
    {
        this->number = RandomGenerator::getRandomNumber(1000, 9999);
    } while(!Number::correct(this->number));

    std::cout << this->intro;
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
                if(t % 10 == b % 10)
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
