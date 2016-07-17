#include <algorithm>
#include <vector>

#include "Number.hpp"

namespace Number
{
    bool correct(const int & t)
    {
        if(t < 1000 || t > 9999)
        {
            return false;
        }

        std::vector<int> d;
        int t_copy = t;
        while(t_copy)
        {
            if(std::find(d.begin(), d.end(), t_copy % 10) != d.end())
            {
                return false;
            }

            d.push_back(t_copy % 10);

            t_copy /= 10;
        }

        return true;
    }
}

