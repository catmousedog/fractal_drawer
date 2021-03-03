
#include "Util.h"

int compare(double E1, double E, double E2)
{

	if (E1 < E)
	{
		if (E2 < E1)
			return Right;
		else if (E1 == E2)
			return Max;
		else
			return Left;
	}
	else if (E2 < E)
	{
		return Right;
	}
	else
	{
		return Min;
	}
}

int sgn(double v)
{
	return (v > 0) - (v < 0);
}

