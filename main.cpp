#include <iostream>
#include <string>
#include <fstream>

#define RED "\033[31;01m"
#define RESET "\033[00m"

int main()
{
    std::ifstream conf_file("resources/ikea");
	if (!conf_file)
	{
		std::cerr << RED << "Error: could not open file." << RESET << std::endl;
		return (1);
	}

    // print file without comment line
    std::string line;
    while (std::getline(conf_file, line))
    {
        if (line[0] != '#')
            std::cout << line << std::endl;
    }
    return (0);
}