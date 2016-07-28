#include <iostream>
#include <vector>
#include <algorithm>

#include "Game.hpp"

struct Game::ResultBC
{
    int bulls = 0;
    int cows = 0;

    ResultBC() { }
    ResultBC(int b, int c) : bulls(b), cows(c) { }
};

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
    "different from zero. All invalid inputs will be discarded.\n"
    "\nPlease refer to the Wikipedia article for more details:\n"
    "https://en.wikipedia.org/wiki/Bulls_and_cows\n\n";

bool Game::isCorrectNumber(int n)
{
    // While chosenNumber is guaranteed to be within the range,
    // user input can be invalid (the case when user enters NaN
    // is processed earlier).
    if(n < 1000 || n > 9999)
    {
        return false;
    }

    // Checking whether we have the same digit twice or more.
    std::vector<int> digits;
    while(n)
    {
        if(std::find(digits.begin(), digits.end(), n % 10) != digits.end())
        {
            return false;
        }

        digits.push_back(n % 10);
        n /= 10;
    }

    // No two same digits were found; number is correct.
    return true;
}

int Game::getUserInput()
{
    int input;
    while(true)
    {
        std::cout << "Please enter your guess: ";
        std::cin >> input;

        if(std::cin.fail() || !isCorrectNumber(input))
        {
            // Clearing error state and the rest of the garbage.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Get rid of any trailing data.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // cin.gcount() returns the number of characters left in
        // the input stream after the last stream extraction operation.
        // Ideally, it's supposed to equal 1, i.e. the newline char
        // only. If there's something else (even a whitespace), the input
        // is considered invalid and is ignored.
        if(std::cin.gcount() > 1)
        {
            continue;
        }

        break;
    }
    return input;
}

Game::ResultBC Game::checkGuess(int g)
{
    // The function is only called for valid inputs, so a guess counts.
    ++guessCounter;

    if(g == chosenNumber)
    {
        return ResultBC(4,0);
    }

    Game::ResultBC res;
    int c = chosenNumber;

    while(g)
    {
        if(g % 10 == c % 10)            // If we got a position match...
        {
            res.bulls++;                // bulls++.
        }
        else                            // ...if no position match...
        {
            int t = chosenNumber;
            while(t)
            {
                if(t % 10 == g % 10)    // ...but found somewhere else...
                {
                    res.cows++;         // cows++.
                    break;
                }
                t /= 10;
            }
        }

        g /= 10;
        c /= 10;
    }

    return res;
}

Game::Game()
{
    guessCounter = 0;

    do
    {
        chosenNumber = RandomGenerator::getRandomNumber(1000, 9999);
    } while(!isCorrectNumber(chosenNumber));

    std::cout << intro;

    // Attempt limit settings hardcoded:
    gameoverMode = true;
    gameoverLimit = 18;
}

void Game::menu()
{
    while(true)
    {
        int g = getUserInput();

        Game::ResultBC res = checkGuess(g);
        std::cout << "There are " << res.bulls << " bulls and "
                  << res.cows << " cows in your guess.\n";

        if(res.bulls == 4)
        {
            std::cout << "\nYou have guessed the number!\nAttempts used: "
                      << guessCounter;

            if(guessCounter < 2)
                std::cout << " (lucky you!)";
            else if(guessCounter < 6)
                std::cout << " (excellent!)";
            else if(guessCounter < 10)
                std::cout << " (well played!)";

            std::cout << "\nThank you for playing!\n";

            break;
        }

        if(gameoverMode && guessCounter == gameoverLimit)
        {
            std::cout << "\nYou have used " << gameoverLimit << " attempts! "
                      << "Game over :(\nThe number was " << chosenNumber
                      << ".\nBetter luck next time. Thank you for playing!\n";
            break;
        }

        std::cout << std::endl;
    }
}
