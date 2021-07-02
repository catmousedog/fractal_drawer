#include "leja.h"

str Leja::GetN()
{
	str s;
	for (int i = 0; i < regions.size(); i++)
	{
		s += std::to_string(i) + ":\t" + std::to_string(regions.at(i).N) + "\n";
		s += "-------------------------------\n";
	}
	return s;
}

str Leja::GetS()
{
	str s;
	for (int i = 0; i < regions.size(); i++)
	{
		s += std::to_string(i) + ":\t" + std::to_string(regions.at(i).s) + "\n";
		s += "-------------------------------\n";
	}
	return s;
}

