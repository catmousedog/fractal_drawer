#pragma once

#include "Region.h"

class Leja
{
public:

	~Leja();

	std::vector<Region*> regions;

	std::vector<Region*> name;

	std::vector<Region*> origins;

	void AddRegion(Region* const region, bool origin);

	void Shift(const Complex shift);

	str GetN();

	str GetS();

};

