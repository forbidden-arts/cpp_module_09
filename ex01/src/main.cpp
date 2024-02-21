#include "../include/RPN.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Wrong number of arguments !" << std::endl;
		return (1);
	}
	try
	{
		RPN::reversePolishNotation(argv[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}