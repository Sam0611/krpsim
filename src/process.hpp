#ifndef __PROCESS__
#define __PROCESS__

#include <string>
#include <vector>
#include <map>

#include "stock.hpp"

class Process
{
    public:
        Process(std::string name);
        ~Process();
        std::string getName() const;
        void add_resource(std::string stock_name, int quantity, int type);
        void add_delay(int delay);

    private:
        Process();
        std::string                 _name;
        std::map<Stock *, int>      _needs;
        std::map<Stock *, int>      _produces;
        int                         _delay;
};

#endif