#include <iostream>
#include <string>
#include <fstream>

#define RED "\033[31;01m"
#define RESET "\033[00m"

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << RED << "Two arguments needed : file and delay" << RESET << std::endl;
        return (1);
    }

    std::ifstream conf_file(av[1]);
	if (!conf_file)
	{
		std::cerr << RED << "Error: no such file or directory : " << av[1] << RESET << std::endl;
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