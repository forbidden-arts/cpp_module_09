#pragma once

#include <string>

double					findRate(std::string date, std::map<int, double> data);
void					checkInput(char *file, std::map<int, double> data);
std::map<int, double> 	readData();
int moveDateBackOneDay	(const std::string& date);
bool ifValidDate		(const std::string& date);
bool ifValidValue		(const std::string& value);
