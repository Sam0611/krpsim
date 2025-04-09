#include "stock.hpp"

Stock::Stock()
{
}

Stock::Stock(std::string name, int quantity) : _name(name), _quantity(quantity)
{
}

Stock::~Stock()
{
}