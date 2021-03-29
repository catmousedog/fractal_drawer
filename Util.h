#pragma once

#include <string>
#include <sstream>
#include <deque>
#include <iomanip>

typedef std::deque<std::string> deq;
typedef std::string str, (*fp)(deq);

enum gradient
{
	Left = -1, Right = 1, Min = 0, Max = 2
};

int compare(double E1, double E, double E2);

int sgn(double v);

void split(const str& s, char delim, deq& elems);

deq split(const str& s, char delim);

str to_string(double d);
