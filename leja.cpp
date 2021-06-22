#include "leja.h"

str Leja::GetN()
{
	str s;
	for (Region& region : regions)
	{
		s += to_string(region.N) + "\n";
	}
	return s;
}

str Leja::GetS()
{
	str s;
	for (Region& region : regions)
	{
		s += to_string(region.s) + "\n";
	}
	return s;
}

