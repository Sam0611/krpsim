#ifndef __STOCK__
#define __STOCK__

#include <string>

class Stock
{
    public:
        Stock(std::string name, int quantity);
        ~Stock();
        std::string getName() const;
    
    private:
        Stock();
        std::string _name;
        int         _quantity;
};

#endif