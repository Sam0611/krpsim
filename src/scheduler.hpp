#ifndef __SCHEDULER__
#define __SCHEDULER__

#include <string>
#include <vector>

#include "process.hpp"

class Scheduler
{
    public:
        Scheduler();
        ~Scheduler();
        void add_stock(std::string name, int quantity);

    private:
        std::vector<Stock *>        _stocks;
        std::vector<Process *>      _processes;
        std::vector<std::string>    _to_optimize;
};

#endif