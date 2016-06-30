#include "Menu.h"

void Menu::ask(Game & g)
{
    while(true)
    {
        int t;
        std::cout << "Please enter your guess: ";
        std::cin >> t;

        if(!Number::correct(t))
        {
            continue;
        }

        auto result = g.guess(t);
        std::cout << "There are " << result.first << " bulls and " <<
                     result.second << " cows in your guess.\n\n";
    }

    return;
}
