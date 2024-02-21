#include "../include/RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &src)
{
	this->_stack = src._stack;
}

RPN	&RPN::operator=(const RPN &src)
{
	this->_stack = src._stack;
	return (*this);
}

std::stack<int> RPN::_stack;

static bool	checkArgCharacters(std::string arg)
{
	for (char c : arg)
	{
		if (!(isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == ' '))
			return false;
	}
	return true;
}

static bool	checkArgFormat(std::string arg)
{
	size_t	i;

	for (i = 0; i < (arg.length() - 1); i++)
	{
		if (i % 2 == 0 && arg[i] == ' ')
			return (false);
		if (i % 2 != 0 && arg[i] != ' ')
			return (false);
	}
	if (arg[i] == ' ' || isdigit(arg[i]) || arg[i - 1] != ' ')
		return (false);
	return (true);
}

void	RPN::reversePolishNotation(std::string arg)
{
	if (!checkArgCharacters(arg) || !checkArgFormat(arg))
		throw RPN::ErrorExeception();
	for (size_t i = 0; i < arg.length(); i += 2)
	{
		if (isdigit(arg[i]))
			_stack.push(std::atoi(&arg[i]));
		else
		{
			if (_stack.size() < 2)
				throw RPN::ErrorExeception();
			int value2 = _stack.top();
			_stack.pop();
			int value1 = _stack.top();
			_stack.pop();
			if (arg[i] == '/' && value2 == 0)
				throw RPN::ErrorDivideByZeroExecption();
			switch (arg[i])
			{
				case '+':
					_stack.push(value1 + value2);
					break ;
				case '-':
					_stack.push(value1 - value2);
					break ;
				case '*':
					_stack.push(value1 * value2);
					break ;
				case '/':
					_stack.push(value1 / value2);
					break ;
				default:
					std::cerr << "Error" << std::endl;
					return ;
			}
		}
	}
	std::cout << _stack.top() << std::endl;
	_stack.pop();
	return;
}

const char	*RPN::ErrorExeception::what(void) const throw()
{
	return ("Error");
}

const char	*RPN::ErrorDivideByZeroExecption::what(void) const throw()
{
	return ("Error: divide by zero");
}