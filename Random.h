#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <algorithm>
#include <ctime>

class Random
{
public:
    static void init();
    static int get();
};

#endif // RANDOM_H_INCLUDED
