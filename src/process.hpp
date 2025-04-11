#ifndef __PROCESS__
#define __PROCESS__

#include <string>
#include <vector>
#include <map>

class Process
{
    public:
        Process(std::string name);
        ~Process();
        std::string getName() const;
        int add_resource(std::string stock_name, int quantity, int type);
        void add_delay(int delay);

    private:
        Process();
        std::string                 _name;
        std::map<std::string, int>  _needs;
        std::map<std::string, int>  _produces;
        int                         _delay;
};

#endif