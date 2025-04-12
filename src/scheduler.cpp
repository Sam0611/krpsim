#include "scheduler.hpp"
#include <iostream>
#include <fstream>

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
    for (size_t i = 0; i < _stocks.size(); i++)
        delete _stocks[i];
    for (size_t i = 0; i < _processes.size(); i++)
        delete _processes[i];
}

int Scheduler::add_stock(std::string name, int quantity)
{
    for (size_t i = 0; i < _stocks.size(); i++)
        if (!name.compare(_stocks[i]->getName()) && name.length() == _stocks[i]->getName().length())
            return (1);

    _stocks.push_back(new Stock(name, quantity));
    return (0);
}

int Scheduler::add_process(std::string name)
{
    // check if a stock has the same name
    for (size_t i = 0; i < _stocks.size(); i++)
        if (!name.compare(_stocks[i]->getName()) && name.length() == _stocks[i]->getName().length())
            return (1);
    
    // check if a process has the same name
    for (size_t i = 0; i < _processes.size(); i++)
        if (!name.compare(_processes[i]->getName()) && name.length() == _processes[i]->getName().length())
            return (1);

    _processes.push_back(new Process(name));
    return (0);
}

int Scheduler::add_to_optimize(std::string name)
{
    // must not already be in 'to optimize' list
    for (size_t i = 0; i < _to_optimize.size(); i++)
        if (!name.compare(_to_optimize[i]) && name.length() == _to_optimize[i].length())
            return (1);
    
    // must be 'time' or an existing stock name
    bool existing = false;
    for (size_t i = 0; i < _stocks.size(); i++)
        if (!name.compare(_stocks[i]->getName()) && name.length() == _stocks[i]->getName().length())
            existing = true;
    std::string authorized_name = "time";
    if (!existing && (name.compare(authorized_name) || name.length() != authorized_name.length()))
        return (1);

    _to_optimize.push_back(name);
    return (0);
}

int Scheduler::add_process_resources(std::string process_name, std::string stock, int quantity, int type)
{
    add_stock(stock, 0);

    // check if stock is a process name
    for (size_t i = 0; i < _processes.size(); i++)
        if (!stock.compare(_processes[i]->getName()) && stock.length() == _processes[i]->getName().length())
            return (1);

    for (size_t i = 0; i < _processes.size(); i++)
    {
        if (!process_name.compare(_processes[i]->getName()) && process_name.length() == _processes[i]->getName().length())
        {
            if (_processes[i]->add_resource(stock, quantity, type))
                return (1);
            break ;
        }
    }

    return (0);
}

void Scheduler::add_process_delay(std::string name, int delay)
{
    for (size_t i = 0; i < _processes.size(); i++)
    {
        if (!name.compare(_processes[i]->getName()) && name.length() == _processes[i]->getName().length())
        {
            _processes[i]->add_delay(delay);
        }
    }
}

int Scheduler::getStockSize() const
{
    return (_stocks.size());
}

int Scheduler::getProcessSize() const
{
    return (_processes.size());
}

int Scheduler::getToOptimizeSize() const
{
    return (_to_optimize.size());
}

void Scheduler::display_stocks(std::ofstream &os, std::string separator) const
{
    for (size_t i = 0; i < _stocks.size(); i++)
    {
        os << _stocks[i]->getName();
        if (i + 1 != _stocks.size())
            os << separator;
    }
    os << std::endl;
}

void Scheduler::display_processes(std::ofstream &os, std::string separator) const
{
    for (size_t i = 0; i < _processes.size(); i++)
    {
        os << _processes[i]->getName();
        if (i + 1 != _processes.size())
            os << separator;
    }
    os << std::endl;
}

void Scheduler::display_to_optimize(std::ofstream &os, std::string separator) const
{
    for (size_t i = 0; i < _to_optimize.size(); i++)
    {
        os << _to_optimize[i];
        if (i + 1 != _to_optimize.size())
            os << separator;
    }
    os << std::endl;
}