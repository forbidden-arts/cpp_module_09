#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	*this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
	if (this != &src)
		this->_dataMap = src._dataMap;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

static int dateToInt(const std::string& dateStr)
{
	std::istringstream iss(dateStr);
	int year, month, day;
	char delimiter;

	if (!(iss >> year >> delimiter >> month >> delimiter >> day) || (delimiter != '-'))
		return 0;

	return year * 10000 + month * 100 + day;
}

static bool isValidDate(const std::string& dateStr)
{
	std::istringstream iss(dateStr);
	int year, month, day;
	char delimiter;

	if (!(iss >> year >> delimiter >> month >> delimiter >> day) || (delimiter != '-'))
		return false;

	std::tm time = {};
	time.tm_year = year - 1900; // Year since 1900
	time.tm_mon = month - 1; // Month index starts from 0
	time.tm_mday = day;

	// Attempt to normalize the date
	std::mktime(&time);

	// Check if the normalized date matches the input date
	return time.tm_year == year - 1900 && time.tm_mon == month - 1 && time.tm_mday == day;
}

static bool checkValue(double value)
{
	if (value < 0.0 || value > 1000.0)
	{
		std::cerr << "Invalid value: " << value << std::endl;
		return false;
	}
	return true;
}

void BitcoinExchange::readCSV(const std::string &filename)
{
	std::ifstream file(filename);
	std::map<int, double> dataMap;

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	std::string line;
	// Skip header
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string dateStr, exchangeRateStr;
		if (std::getline(iss, dateStr, ',') && std::getline(iss, exchangeRateStr, ','))
		{
			try
			{
				double exchangeRate = std::stod(exchangeRateStr);
				int dateInt = dateToInt(dateStr);
				dataMap[dateInt] = exchangeRate;
			}
			catch (const std::invalid_argument& e)
			{
				std::cerr << "Invalid exchange rate value: " << exchangeRateStr << std::endl;
				continue;
			}
		}
		else
		{
			std::cerr << "Invalid line: " << line << std::endl;
			continue;
		}
	}

	file.close();
	_dataMap = dataMap;
}

bool BitcoinExchange::validateDate(const std::string& inputDate)
{
	std::istringstream iss(inputDate);
	std::string dateStr, pipe, valueStr;
	int earliestDate = _dataMap.begin()->first;
	int latestDate = _dataMap.rbegin()->first;

	iss >> dateStr >> pipe >> valueStr;
	if (dateStr.empty() || pipe != "|" || valueStr.empty())
		return false;

	if (!isValidDate(dateStr))
		return false;

	int dateInt = dateToInt(dateStr);

	if (dateInt < earliestDate || dateInt > latestDate)
	{
		std::cerr << "Out of range. ";
		return false;
	}
	return true;
}

void BitcoinExchange::searchValue(std::string input)
{
	std::string line, dateStr, pipe;
	int value;
	std::ifstream inputFile;
	std::istringstream iss(line);

	readCSV(DATAFILE);
	if (_dataMap.empty())
	{
		std::cerr << "No data available" << std::endl;
		return;
	}
	inputFile.open(input);
	if (!inputFile.is_open())
	{
		std::cerr << "Error opening file: " << input << std::endl;
		return;
	}
	getline(inputFile, line);
	if (line.empty() || line != "date | value")
	{
		std::cerr << "Error. First line must be header: \"date | value\"" << std::endl;
		return;
	}
	while (getline(inputFile, line))
	{
		if (line.empty())
			continue;
		if (!validateDate(line))
		{
			std::cerr << "Invalid date: " << line << std::endl;
			continue;
		}
		iss >> dateStr >> pipe >> value;
		if (!checkValue(value))
		{
			std::cerr << "Invalid value: " << value << std::endl;
			continue;
		}
		int inputDateInt = dateToInt(dateStr);

		// Check if the date exists in _dataMap
		std::map<int, double>::iterator it = _dataMap.lower_bound(inputDateInt);
		if (it->first != inputDateInt)
		{
			// Date does not exist, get the next lower date
			if (it != _dataMap.begin())
			{
				--it;
				inputDateInt = it->first;
			}
		}
		std::cout << dateStr << " => " << value << " = " << (value * it->second) << std::endl;
	}
}