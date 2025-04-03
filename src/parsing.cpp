#include "parsing.hpp"

#define STOCK_LINE 1
#define PROCESS_LINE 2
#define OPTIMIZE_LINE 3

bool    parse_file(std::string filename)
{
    std::ifstream conf_file(filename);
    if (!conf_file)
	{
		std::cerr << RED << "Error: no such file or directory : " << filename << RESET << std::endl;
		return (false);
	}

    std::string line;
    int line_type = 0;
    bool relevant_line = false;
    while (std::getline(conf_file, line))
    {

        if (!is_relevant_line(line))
        {
            relevant_line = false;
            continue ;
        }
        
        if (!relevant_line)
        {
            relevant_line = true;
            line_type++;
        }

        if (!parse_line(line, line_type))
            return (false);
    }

    return (true);
}

bool    parse_line(std::string line, int type)
{
    switch (type)
    {
        case STOCK_LINE:
            return (parse_stock_line(line));
        case PROCESS_LINE:
            return(parse_process_line(line));
        case OPTIMIZE_LINE:
            return(parse_optimize_line(line));
    }

    return (false);
}

// stockA:10
bool    parse_stock_line(std::string line)
{
    std::string stock;

    std::size_t i = 0;
    while (isspace(line[i]))
        i++;

    std::size_t pos = line.find(':');
    if (pos == std::string::npos)
    {
        std::cerr << RED << "Error: Missing ':' in stock line" << RESET << std::endl;
        return (false);
    }

    // get stock name and check it
    stock = line.substr(i, pos - i);
    if (!check_name(stock))
        return (false);

    // save stock name

    // check quantity after ':'
    i = pos + 1;
    while (line[i])
    {
        if (!isdigit(line[i]))
        {
            std::cerr << RED << "Error: Stock quantity is not a valid number" << RESET << std::endl;
            return (false);
        }
        i++;
    }

    // save stock quantity line.substr(pos + 1)

    return (true);
}

// process_name:(stockA:5;stockB:10):(stockC:1):10
bool    parse_process_line(std::string line)
{
    std::string process;

    int i = 0;
    while (isspace(line[i]))
        i++;

    std::size_t pos = line.find(':');
    if (pos == std::string::npos)
    {
        std::cerr << RED << "Error: Missing ':' in process line" << RESET << std::endl;
        return (false);
    }

    // get process name and check it
    process = line.substr(i, pos - i);
    if (!check_name(process))
        return (false);

    // save process name

    // check after first ':'

    return (true);
}

// optimize:(stockC;time)
bool    parse_optimize_line(std::string line)
{
    int i = 0;
    while (isspace(line[i]))
        i++;

    std::size_t pos = line.find(':');
    if (pos == std::string::npos)
    {
        std::cerr << RED << "Error: Missing ':' in optimize line" << RESET << std::endl;
        return (false);
    }

    // check optimize word
    std::string word = "optimize";
    if (line.substr(i, pos - i).compare(word) == 0 || word.length() != line.substr(i, pos - i).length())
    {
        std::cerr << RED << "Error: 'optimize' expression is missing or misspelled" << RESET << std::endl;
        return (false);
    }

    // check after ':'

    return (true);
}

// not valid : a__b, _a, a_, a1, a-b
// valid : abc, abc_abc, a_a_a, A
bool    check_name(std::string name)
{
    int i = 0;
    while (name[i])
    {
        if (name[i] == '_')
        {
            if (i == 0 || !name[i + 1] || name[i + 1] == '_')
            {
                std::cerr << RED << "Error: Invalid name: " << name << " must have underscore surrounded by letters" << RESET << std::endl;
                return (false);
            }
        }
        else if (!isalpha(name[i]))
        {
            std::cerr << RED << "Error: Invalid name: " << name << " must only contain letters or underscores" << RESET << std::endl;
            return (false);
        }
        i++;
    }

    return (true);
}

// return false if line is a comment, is empty or only whitespaces
bool    is_relevant_line(std::string line)
{
    int i = 0;
    while (isspace(line[i]))
        i++;

    if (line[i] == '#' || !line[i])
        return (false);

    return (true);
}

// special characters authorized " : ; ( ) "
bool    is_special_char(char c)
{
    if (c == ':' || c == ';' || c == '(' || c == ')')
        return (true);
    return (false);
}