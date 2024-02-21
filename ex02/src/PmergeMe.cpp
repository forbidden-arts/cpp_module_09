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

	Container result;
	typename Container::iterator it;

	// Analyze pairs of elements and push the greater of the two into the container S
	for (it = source.begin(); it != source.end() && it + 1 != source.end(); it += 2)
	{
		// Determine the greater element between *it and *(it + 1)
		int bigNum;
		if (*it > *(it + 1))
			bigNum = *it;
		else
			bigNum = *(it + 1);
		result.push_back(bigNum);
	}

	result = algorithm(result); // Recurse

	// Inserting elements based on binary search
	for (it = source.begin(); it != source.end() && it + 1 != source.end(); it += 2)
	{
		// Determine the smaller element between *it and *(it + 1)
		int smallNum;
		if (*it < *(it + 1))
			smallNum = *it;
		else
			smallNum = *(it + 1);
		// Perform binary search to find the position to insert the smaller element
		result.insert(binarySearch(result, smallNum), smallNum);
	}

	// Handle last element
	if (source.size() % 2 != 0)
		result.insert(binarySearch(result, *(source.end() - 1)), *(source.end() - 1));

	return result;
}

// Explicit template instantiations for vector and deque
template class PmergeMe<std::vector<int>>;
template class PmergeMe<std::deque<int>>;
