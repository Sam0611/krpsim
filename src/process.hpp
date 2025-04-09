#ifndef __PROCESS__
#define __PROCESS__

#include <string>
#include <vector>
#include <map>

#include "stock.hpp"

class Process
{
    public:
        Process();
        ~Process();

    private:
        std::map<Stock *, int>      _needs;
        std::map<Stock *, int>      _produces;
        std::vector<std::string>    _to_optimize;
        int                         _delay;
};

#endif