#include "parsing.hpp"

#define STOCK_LINE 1
#define PROCESS_LINE 2
#define OPTIMIZE_LINE 3
#define NEEDED 1
#define PRODUCED 2

bool    parse_file(std::string filename, Scheduler &scheduler)
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
        // if line is a comment or is empty, it's not relevant
        if (!is_relevant_line(line))
        {
            relevant_line = false;
            continue ;
        }

        // if there is relevant lines after optimize line
        if (line_type == OPTIMIZE_LINE)
        {
            std::cerr << RED << "Error: the file must end with one line indicating what to optimize" << RESET << std::endl;
            return (false);
        }
        
        if (!relevant_line)
        {
            relevant_line = true;
            line_type++;
        }

        if (!parse_line(line, line_type, scheduler))
            return (false);
    }

    // check if file contains all elements
    if (line_type != OPTIMIZE_LINE)
    {
        std::cerr << RED << "Error: the file must contain at least one stock, one process, and exactly one line to indicate what to optimize" << RESET << std::endl;
        return (false);
    }

    return (true);
}

bool    parse_line(std::string line, int type, Scheduler &scheduler)
{
    switch (type)
    {
        case STOCK_LINE:
            return (parse_stock_line(line, scheduler));
        case PROCESS_LINE:
            return(parse_process_line(line, scheduler));
        case OPTIMIZE_LINE:
            return(parse_optimize_line(line, scheduler));
    }

    return (false);
}

// stockA:10
bool    parse_stock_line(std::string line, Scheduler &scheduler)
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

    // check quantity after ':'
    i = pos + 1;

    if (!line[i])
    {
        std::cerr << RED << "Error: Stock quantity is missing" << RESET << std::endl;
        return (false);
    }

    while (line[i])
    {
        if (!isdigit(line[i]))
        {
            std::cerr << RED << "Error: Stock quantity '" << line.substr(pos + 1) << "' is not a valid number" << RESET << std::endl;
            return (false);
        }
        i++;
    }

    if (scheduler.add_stock(stock, atoi(line.substr(pos + 1).c_str())))
    {
        std::cerr << RED << "Error: " << stock << " already exists" << RESET << std::endl;
        return (false);
    }

    return (true);
}

// process_name:(stockA:5;stockB:10):(stockC:1):10
bool    parse_process_line(std::string line, Scheduler &scheduler)
{
    std::string process;
    std::string delay;

    std::size_t i = 0;
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

    if (scheduler.add_process(process))
    {
        std::cerr << RED << "Error: " << process << " already exists" << RESET << std::endl;
        return (false);
    }

    // check after first ':' until '):'
    if (!check_process_resources(line.substr(pos + 1), scheduler, process, NEEDED))
        return (false);

    // get line after '):'
    line = line.substr(line.find(')') + 2);

    // check second process resources group until '):'
    if (!check_process_resources(line, scheduler, process, PRODUCED))
        return (false);

    // check last element (delay) after '):' is a valid number
    i = line.find(')') + 2;

    if (!line[i])
    {
        std::cerr << RED << "Error: Process delay missing" << RESET << std::endl;
        return (false);
    }

    delay = line.substr(i);

    for (i = 0; i < delay.length(); i++)
    {
        if (!isdigit(delay[i]))
        {
            std::cerr << RED << "Error: Process delay is not a valid number" << RESET << std::endl;
            return (false);
        }
    }

    scheduler.add_process_delay(process, atoi(delay.c_str()));

    return (true);
}

// (name:qt):
// (name:qt;name:qt):
bool    check_process_resources(std::string resources, Scheduler &scheduler, std::string process_name, int type)
{
    // check parenthesis
    std::size_t end = resources.find(')');
    if (resources[0] != '(' || end == std::string::npos)
    {
        std::cerr << RED << "Error: Missing or misplaced parenthesis in process line" << RESET << std::endl;
        return (false);
    }
    
    // check process resources separator ':' after parenthesis
    if (resources[end + 1] != ':')
    {
        std::cerr << RED << "Error: Missing or misplaced ':' in process line" << RESET << std::endl;
        return (false);
    }

    // check content between parenthesis

    std::size_t start;
    std::string stock;
    std::string quantity;
    
    while (resources[0] != ')')
    {
        // check stock name
        start = 1;
        end = resources.find(':');
        if (end == resources.find(')') + 1)
        {
            std::cerr << RED << "Error: Missing ':' in process line" << RESET << std::endl;
            return (false);
        }
        stock = resources.substr(start, end - start);
        if (!check_name(stock))
            return (false);

        // check stock quantity
        start = end + 1;
        while (resources[end] != ';' && resources[end] != ')')
            end++;
        quantity = resources.substr(start, end - start);
        if (!check_quantity(quantity))
            return (false);

        if (scheduler.add_process_resources(process_name, stock, atoi(quantity.c_str()), type))
        {
            std::cerr << RED << "Error: Incorrect stock name '" << stock << "' in process ressources" << RESET << std::endl;
            return (false);
        }

        // cut resources checked from resources group
        resources = resources.substr(end);
    }

    return (true);
}

// optimize:(stock_name;time)
bool    parse_optimize_line(std::string line, Scheduler &scheduler)
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
    if (line.substr(i, pos - i).compare(word) || word.length() != line.substr(i, pos - i).length())
    {
        std::cerr << RED << "Error: 'optimize' expression is missing or misspelled" << RESET << std::endl;
        return (false);
    }

    // check after ':'
    return (check_stock_to_optimize(line.substr(pos + 1), scheduler));
}

// (time)
// (stock;time)
bool    check_stock_to_optimize(std::string to_optimize, Scheduler &scheduler)
{
    // check parenthesis
    std::size_t end = to_optimize.find(')');
    if (to_optimize[0] != '(' || end == std::string::npos)
    {
        std::cerr << RED << "Error: Missing or misplaced parenthesis in optimize line" << RESET << std::endl;
        return (false);
    }

    // check content between parenthesis

    std::size_t start;
    std::string stock;
    std::string authorized_name = "time";
    
    while (to_optimize[0] != ')')
    {
        // check stock name
        start = 1;
        end = 1;

        while (to_optimize[end] != ';' && to_optimize[end] != ')')
            end++;

        stock = to_optimize.substr(start, end - start);
        if (stock.compare(authorized_name) || stock.length() != authorized_name.length())
            if (!check_name(stock))
                return (false);

        if (scheduler.add_to_optimize(stock))
        {
            std::cerr << RED << "Error: optimize line: stock name is incorrect" << RESET << std::endl;
            return (false);
        }

        // cut to_optimize checked from to_optimize group
        to_optimize = to_optimize.substr(end);
    }

    // check there is nothing after parenthesis
    if (to_optimize.length() > 1)
    {
        std::cerr << RED << "Error: optimize line: something was found after parenthesis" << RESET << std::endl;
        return (false);
    }

    return (true);
}

// not valid : a__b, _a, a_, a-b, 1, 1a
// valid : abc, abc_abc, a_a_a, A, a1, a_1
bool    check_name(std::string name)
{
    if (name.empty())
    {
        std::cerr << RED << "Error: Missing name for stock or process" << RESET << std::endl;
        return (false);
    }

    std::string forbidden_name = "optimize";
    if (!name.compare(forbidden_name) && name.length() == forbidden_name.length())
    {
        std::cerr << RED << "Error: '" << forbidden_name << "' is a forbidden name !" << RESET << std::endl;
        return (false);
    }

    forbidden_name = "time";
    if (!name.compare(forbidden_name) && name.length() == forbidden_name.length())
    {
        std::cerr << RED << "Error: '" << forbidden_name << "' is a forbidden name !" << RESET << std::endl;
        return (false);
    }

    if (isdigit(name[0]))
    {
        std::cerr << RED << "Error: Invalid name: " << name << " cannot begin with a digit" << RESET << std::endl;
        return (false);
    }

    int i = 0;
    while (name[i])
    {
        if (name[i] == '_')
        {
            if (i == 0 || !name[i + 1] || name[i + 1] == '_')
            {
                std::cerr << RED << "Error: Invalid name: " << name << " must have underscore surrounded by letters or digits" << RESET << std::endl;
                return (false);
            }
        }
        else if (!isalnum(name[i]))
        {
            std::cerr << RED << "Error: Invalid name: " << name << " must only contain letters, digits or underscores" << RESET << std::endl;
            return (false);
        }
        i++;
    }

    return (true);
}

bool    check_quantity(std::string quantity)
{
    if (quantity.empty())
    {
        std::cerr << RED << "Error: Missing stock quantity in a process" << RESET << std::endl;
        return (false);
    }

    int i = 0;
    while (quantity[i])
    {
        if (!isdigit(quantity[i]))
        {
            std::cerr << RED << "Error: Stock quantity '"<< quantity <<"' is not a valid number" << RESET << std::endl;
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