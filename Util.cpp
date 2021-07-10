
#include "Util.h"

str GetPathCoeff(int i)
{
	return "data\\coeff\\segment_" + to_string(i) + ".txt";
}

str GetPathLeja(int i)
{
	return "data\\leja\\segment_" + to_string(i) + ".txt";
}

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
