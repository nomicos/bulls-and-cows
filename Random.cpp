#include "Random.h"

namespace Random
{
    void init()
    {
        srand(time(nullptr));
        rand(); // Skipping the first-ever generated number.
    }

    int get()
    {
        return rand();
    }
}

