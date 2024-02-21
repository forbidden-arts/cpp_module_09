#include "../include/PmergeMe.hpp"

// Default constructor
template<typename Container>
PmergeMe<Container>::PmergeMe()
{
}

// Copy constructor
template<typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe<Container>&)
{
}

// Copy assignment operator
template<typename Container>
PmergeMe<Container>& PmergeMe<Container>::operator=(const PmergeMe<Container>&)
{
	return *this;
}

// Destructor
template<typename Container>
PmergeMe<Container>::~PmergeMe()
{
}

template<typename Container>
static typename Container::iterator binarySearch(Container& A, int target)
{
	// Using auto because the type of the iterator is not known
	auto left = A.begin();
	auto right = A.end() - 1;
	while (left <= right)
	{
		auto mid = left + (right - left) / 2;
		if (*mid < target)
			left = mid + 1;
		else if (*mid > target)
		{
			if (mid == A.begin())
				break;
			right = mid - 1;
		}
		else
			return mid;
	}
	return left;
}

template<typename Container>
Container PmergeMe<Container>::algorithm(Container source)
{
	if (source.size() <= 1)
		return source; // Base case for recursion

	Container destination;
	typename Container::iterator it;

	// Analyze pairs of elements and push the greater of the two into the container S
	for (it = source.begin(); it != source.end() && it + 1 != source.end(); it += 2)
	{
		// Determine the greater element between *it and *(it + 1)
		int greaterElement;
		if (*it > *(it + 1))
			greaterElement = *it;
		else
			greaterElement = *(it + 1);
		destination.push_back(greaterElement);
	}

	destination = algorithm(destination); // Recurse

	// Inserting elements based on binary search
	for (it = source.begin(); it != source.end() && it + 1 != source.end(); it += 2)
	{
		// Determine the smaller element between *it and *(it + 1)
		int smallerElement;
		if (*it < *(it + 1))
			smallerElement = *it;
		else
			smallerElement = *(it + 1);
		// Perform binary search to find the position to insert the smaller element
		destination.insert(binarySearch(destination, smallerElement), smallerElement);
	}

	// Handle last element
	if (source.size() % 2 != 0)
		destination.insert(binarySearch(destination, *(source.end() - 1)), *(source.end() - 1));

	return destination;
}

// Explicit template instantiations for vector and deque
template class PmergeMe<std::vector<int>>;
template class PmergeMe<std::deque<int>>;
