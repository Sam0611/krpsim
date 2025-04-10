#ifndef __PARSING__
#define __PARSING__

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> // atoi
#include <cctype> // isspace, isalnum, isdigit
#include "scheduler.hpp"

#define RED "\033[31;01m"
#define RESET "\033[00m"

// used in main

bool    parse_file(std::string filename, Scheduler &scheduler);


// used in parsing

bool    parse_line(std::string line, int type, Scheduler &scheduler);

bool    parse_stock_line(std::string line, Scheduler &scheduler);
bool    parse_process_line(std::string line, Scheduler &scheduler);
bool    parse_optimize_line(std::string line, Scheduler &scheduler);

bool    check_process_resources(std::string resources, Scheduler &scheduler, std::string process_name, int type);
bool    check_stock_to_optimize(std::string to_optimize, Scheduler &scheduler);

bool    is_relevant_line(std::string line);
bool    check_name(std::string name);
bool    check_quantity(std::string quantity);

#endif