
#include "parsing.hpp"

void    save_output(std::ofstream &file, std::string output)
{
    std::cout << output << std::endl;
    file << output << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cerr << RED << "Two arguments needed : file and delay" << RESET << std::endl;
        return (1);
    }

    if (!parse_file(av[1]))
        return (1);

    
    // std::ofstream output_file("krpsim_output");
    // std::string line;
    // while (std::getline(conf_file, line))
    // {
    //     if (line[0] != '#')
    //     {
    //         save_output(output_file, line);
    //     }
    // }
    // output_file.close();

    return (0);
}