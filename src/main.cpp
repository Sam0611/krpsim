
#include "parsing.hpp"
#include "scheduler.hpp"

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

    Scheduler scheduler;

    if (!parse_file(av[1], scheduler))
        return (1);

    // save output in file

    std::string filename = "krpsim_output";
    std::ofstream output_file(filename);

    output_file << "There are " << scheduler.getStockSize() << " stocks: ";
    scheduler.display_stocks(output_file, ", ");

    output_file << "There are " << scheduler.getProcessSize() << " processes: ";
    scheduler.display_processes(output_file, ", ");

    output_file << "There are " << scheduler.getToOptimizeSize() << " to optimize: ";
    scheduler.display_to_optimize(output_file, ", ");

    output_file.close();

    // read output file
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
        std::cout << line << std::endl;

    return (0);
}