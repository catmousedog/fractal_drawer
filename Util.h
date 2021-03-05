#pragma once

#include <string>
#include <sstream>
#include <deque>
#include <iomanip>

enum gradient
{
	Left = -1, Right = 1, Min = 0, Max = 2
};

int compare(double E1, double E, double E2);

int sgn(double v);

void split(const std::string& s, char delim, std::deque<std::string>& elems);

std::deque<std::string> split(const std::string& s, char delim);

std::string to_string(double d);
