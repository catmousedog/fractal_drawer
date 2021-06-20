#include "leja.h"

#define PI 3.1415926
#define T 2*PI*t

Leja::Leja()
{
	auto X1 = [](double t) -> double
	{
		return sin(T) + cos(4*T);
	};
	auto Y1 = [](double t) -> double
	{
		return 3 * (cos(T) + sin(T));
	};
	regions.push_back(Region(2000, X1, Y1));

	auto X2 = [](double t) -> double
	{
		return sin(T) - 5;
	};
	auto Y2 = [](double t) -> double
	{
		return cos(T);
	};
	regions.push_back(Region(2000, X2, Y2));


}

void Leja::Add(int N)
{
	this->N += N;
	for (Region& region : regions)
	{
		region.Add(N);
	}
}
