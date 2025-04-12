#ifndef __SCHEDULER__
#define __SCHEDULER__

#include <string>
#include <vector>

#include "stock.hpp"
#include "process.hpp"

class Scheduler
{
    public:
        Scheduler();
        ~Scheduler();
        int add_stock(std::string name, int quantity);
        int add_process(std::string name);
        int add_process_resources(std::string process_name, std::string stock, int quantity, int type);
        void add_process_delay(std::string name, int delay);
        int add_to_optimize(std::string name);
        int getStockSize() const;
        int getProcessSize() const;
        int getToOptimizeSize() const;
        void display_stocks(std::ofstream &os, std::string separator) const;
        void display_processes(std::ofstream &os, std::string separator) const;
        void display_to_optimize(std::ofstream &os, std::string separator) const;

    private:
        std::vector<Stock *>        _stocks;
        std::vector<Process *>      _processes;
        std::vector<std::string>    _to_optimize;
};

#endif