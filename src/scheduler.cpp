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