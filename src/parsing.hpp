#ifndef __PARSING__
#define __PARSING__

#include <string>
#include <iostream>
#include <fstream>
#include <cctype> // isspace, isalpha

#define RED "\033[31;01m"
#define RESET "\033[00m"

// used in main
bool    parse_file(std::string filename);

// used in parsing
bool    parse_line(std::string line, int type);
bool    is_relevant_line(std::string line);
bool    is_special_char(char c);
bool    check_name(std::string name);
bool    check_quantity(std::string quantity);
bool    parse_stock_line(std::string line);
bool    parse_process_line(std::string line);
bool    parse_optimize_line(std::string line);
bool    check_process_resources(std::string resources);

#endif