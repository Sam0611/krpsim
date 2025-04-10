#include <iostream>
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

void Process::add_resource(std::string stock_name, int quantity, int type)
{
    if (type == NEEDED)
    {
        std::cout << stock_name << " : " << quantity << " is needed" << std::endl;
    }
    else if (type == PRODUCED)
    {
        std::cout << stock_name << " : " << quantity << " is produced" << std::endl;
    }
}

void Process::add_delay(int delay)
{
    _delay = delay;
}