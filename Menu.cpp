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
                     result.second << " cows in your guess.\n";

        if(result.first == 4)
        {
            std::cout << "You have guessed the number having used " <<
            g.getGuessCounter() << " attempts.\nThank you for playing!\n\n";
            break;
        }

        std::cout << std::endl;
    }

    return;
}
