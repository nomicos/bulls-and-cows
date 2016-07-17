#include <algorithm>
#include <ctime>

#include "RandomGenerator.hpp"

namespace RandomGenerator
{
    void initSeed()
    {
        srand(time(nullptr));
        rand(); // Skipping the first-ever generated number.
    }

    // I am not quite completely sure how this works, but I found it
    // on this nice C++ tutorial website, and it does work, so...
    int getRandomNumber(int min, int max)
    {
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }
}

