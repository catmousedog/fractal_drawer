
#include "Util.h"


int sgn(double v)
{
	return (v > 0) - (v < 0);
}

void split(const str& s, char delim, deq& elems) {
	std::stringstream ss(s);
	str item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}


deq split(const str& s, char delim) {
	deq elems;
	split(s, delim, elems);
	return elems;
}

str to_string(double d)
{
	std::ostringstream stm;
	stm << std::setprecision(std::numeric_limits<double>::max_digits10) << d;
	return stm.str();
}
