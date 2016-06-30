#include "Random.h"

void Random::init()
{
    srand(time(nullptr));
    rand(); // Skipping the first-ever generated number.
}

int Random::get()
{
    return rand();
}
