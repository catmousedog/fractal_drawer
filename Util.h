#pragma once

#include <string>
#include <sstream>
#include <deque>

enum gradient
{
	Left, Right, Min, Max
};

int compare(double E1, double E, double E2);

int sgn(double v);

void split(const std::string& s, char delim, std::deque<std::string>& elems);

std::deque<std::string> split(const std::string& s, char delim);

