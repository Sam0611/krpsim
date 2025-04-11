#include "process.hpp"

#define NEEDED 1
#define PRODUCED 2

Process::Process() : _delay(0)
{
}

Process::Process(std::string name) : _name(name), _delay(0)
{
}

Process::~Process()
{
}

std::string Process::getName() const
{
    return (_name);
}

int Process::add_resource(std::string stock_name, int quantity, int type)
{ 
    // check if stock name exists in the group of resources before adding it
    
    if (type == NEEDED)
    {
        if (_needs.count(stock_name))
            return (1);
        _needs[stock_name] = quantity;
    }
    else if (type == PRODUCED)
    {
        if (_produces.count(stock_name))
            return (1);
        _produces[stock_name] = quantity;
    }

    return (0);
}

void Process::add_delay(int delay)
{
    _delay = delay;
}