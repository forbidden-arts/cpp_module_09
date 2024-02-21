#pragma once

#include <stack>
#include <cstdlib>
#include <iostream>



class	RPN {

	private:
		static std::stack<int>	_stack;
		RPN();
		RPN(const RPN &src);
		~RPN();
		RPN &operator=(const RPN &src);

	public:
		static void	reversePolishNotation(std::string arg);

		class	ErrorExeception : public std::exception
		{
			public:
				virtual const char	*what(void) const throw();
		};
		class	ErrorDivideByZeroExecption : public std::exception
		{
			public:
				virtual const char	*what(void) const throw();
		};
};