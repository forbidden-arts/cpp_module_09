#pragma once

#include <deque>
#include <vector>
#include <locale>
#include <iomanip>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <type_traits>

template<typename Container>
class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe&);
	PmergeMe& operator=(const PmergeMe&);
	virtual ~PmergeMe();

	static Container algorithm(Container X);

	class BadInputsException : public std::exception
	{
	public:
		virtual const char *what() const throw() override
		{
			return "Bad inputs provided to the algorithm.";
		}
	};
};
