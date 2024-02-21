
#include "../include/BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "One argument required." << std::endl;
		return (1);
	}
	BitcoinExchange::searchValue(argv[1]);
	return (0);
}