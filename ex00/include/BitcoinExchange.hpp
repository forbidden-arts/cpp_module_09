#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

#define DATAFILE "data.csv"

class	BitcoinExchange
{

	private:
		static std::map<int, double> _dataMap;
		static void readCSV(const std::string& filename);
		static bool validateDate(const std::string& inputDate);

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);

	public:

		~BitcoinExchange();
		BitcoinExchange &operator=(const BitcoinExchange& src);

		static void	searchValue(std::string input);
};
