#include "leja.h"

Leja::~Leja()
{
	for (Region* region : regions)
	{
		delete region;
	}
}

void Leja::AddRegion(Region* const region, bool origin)
{
	regions.push_back(region);
	if (origin)
		origins.push_back(region);
	else
		name.push_back(region);
}

void Leja::Shift(const Complex shift)
{
	for (Region* region : name)
	{
		for (Complex& l : region->points)
		{
			l += shift;
		}
		region->coeff.at(region->coeff.size() / 2) += shift;
		for (Complex& b : region->boundary)
		{
			b += shift;
		}
	}
}

str Leja::GetN()
{
	str s;
	for (int i = 0; i < regions.size(); i++)
	{
		s += std::to_string(i) + ":\t" + std::to_string(regions.at(i)->N) + "\n";
		s += "-------------------------------\n";
	}
	return s;
}

str Leja::GetS()
{
	str s;
	for (int i = 0; i < regions.size(); i++)
	{
		s += std::to_string(i) + ":\t" + std::to_string(regions.at(i)->s) + "\n";
		s += "-------------------------------\n";
	}
	return s;
}

