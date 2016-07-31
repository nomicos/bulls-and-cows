#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

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
    using namespace std;
    int input;
    bool isValid;
    do
    {
        try
        {
            // Default assumption.
            isValid = true;

            string rawInput;
            cout << "Please enter your guess ";
            if(gameoverMode)
                cout << "(" << guessCounter+1 << "/" << gameoverLimit << "): ";
            else
                cout << "#" << guessCounter+1 << ": ";
            getline(cin, rawInput);
            cin.clear(); // Fix for when rawInput is '^Z'.

            stringstream iss(rawInput);
            iss >> input;

            if(iss.fail())
            {
                iss.clear();
                iss.ignore(numeric_limits<streamsize>::max(), '\n');
                throw "invalid format";
            }
            if(rawInput.length() != 4)
            {
                throw "too long";
            }
            if(!isCorrectNumber(input))
            {
                throw "invalid number";
            }
        }
        catch(const char * e)
        {
            cerr << "Invalid input: " << e << ".\n\n";
            isValid = false;
        }
    } while(!isValid);
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
    using namespace std;
    bool isEnded = false;
    do
    {
        int g = getUserInput();
        Game::ResultBC res = checkGuess(g);
        cout << "There are " << res.bulls << " bulls and "
                  << res.cows << " cows in your guess.\n";

        if(res.bulls == 4)
        {
            cout << "\nYou have guessed the number.\nAttempts used: "
                      << guessCounter;

            if(guessCounter < 2)
                cout << " (lucky you!)";
            else if(guessCounter < 7)
                cout << " (excellent!)";
            else if(guessCounter < 10)
                cout << " (well played!)";

            cout << "\nThank you for playing!\n";

            isEnded = true;
        }
        else if(gameoverMode && guessCounter == gameoverLimit)
        {
            cout << "\nYou have used " << gameoverLimit << " attempts! "
                      << "Game over :(\nThe number was " << chosenNumber
                      << ".\nBetter luck next time. Thank you for playing!\n";
            isEnded = true;
        }
        cout << endl;
    } while(!isEnded);
}
