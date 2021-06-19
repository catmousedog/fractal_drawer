#pragma once

#include <string>
#include <sstream>
#include <deque>
#include <iomanip>

typedef std::deque<std::string> deq;
typedef std::string str, (*fp)(deq);

int sgn(double v);

void split(const str& s, char delim, deq& elems);

deq split(const str& s, char delim);

str to_string(double d);
