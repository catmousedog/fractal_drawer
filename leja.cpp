#include "leja.h"


str Leja::GetS()
{
	str s;
	for (Region& region : regions)
	{
		s += to_string(region.s) + "\n";
	}
	return s;
}

