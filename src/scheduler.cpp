#include "scheduler.hpp"

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
    // delete all pointers in _stocks and _processes
}

void Scheduler::add_stock(std::string name, int quantity)
{
    _stocks.push_back(new Stock(name, quantity));
}

void Scheduler::add_process(std::string name)
{
    _processes.push_back(new Process(name));
}

void Scheduler::add_to_optimize(std::string name)
{
    _to_optimize.push_back(name);
}

void Scheduler::add_process_resources(std::string process_name, std::string stock, int quantity, int type)
{
    for (size_t i = 0; i < _processes.size(); i++)
    {
        if (process_name.compare(_processes[i]->getName()) == 0)
        {
            _processes[i]->add_resource(stock, quantity, type);
        }
    }
}

void Scheduler::add_process_delay(std::string name, int delay)
{
    for (size_t i = 0; i < _processes.size(); i++)
    {
        if (name.compare(_processes[i]->getName()) == 0)
        {
            _processes[i]->add_delay(delay);
        }
    }
}