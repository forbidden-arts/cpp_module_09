#include <sstream>
#include "../include/PmergeMe.hpp"

template <typename T>
static void	print(const T &container, std::string message)
{
	std::cout << message << std::flush;
	for (typename T::const_iterator	it = container.begin(); it != container.end(); it++)
		std::cout << " " << *it << std::flush;
	std::cout << std::endl;
}

static bool checkNumbers(char** argv) {
	for (int i = 1; argv[i]; i++)
	{
		std::istringstream iss(argv[i]);
		int value;
		if (!(iss >> value) || value < 0)
			return false;
	}
	return true;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: you must enter one or more numbers" << std::endl;
		return 1;
	}

	try
	{
		std::deque<int> deque;
		std::vector<int> vector;
		double vectorTime, dequeTime;
		clock_t mainStart, vectorEnd, dequeEnd;

		if (!checkNumbers(argv))
			throw PmergeMe<std::vector<int>>::BadInputsException();
		for (int i = 1; argv[i]; i++)
		{
			vector.push_back(std::atoi(argv[i]));
			deque.push_back(std::atoi(argv[i]));
		}
		print(vector, "Before:\t");
		mainStart = clock();
		vector = PmergeMe<std::vector<int>>::algorithm(vector);
		vectorEnd = clock();
		vectorTime = (vectorEnd - mainStart) / static_cast<double>(CLOCKS_PER_SEC) * 10.0;
		mainStart = clock();
		deque = PmergeMe<std::deque<int>>::algorithm(deque);
		dequeEnd = clock();
		dequeTime = (dequeEnd - vectorEnd) / static_cast<double>(CLOCKS_PER_SEC) * 10.0;
		print(vector, "After:\t");
		std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << std::flush;
		std::cout << std::fixed << std::setprecision(5) << vectorTime << " us" << std::endl;
		std::cout << "Time to process a range of " << deque.size() << " elements with std::deque : " << std::flush;
		std::cout << std::fixed << std::setprecision(5) << dequeTime << " us" << std::endl;
	}
	catch(std::exception &exep)
	{
		std::cerr << exep.what() << std::endl;
	}
	return 0;
}