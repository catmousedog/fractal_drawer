#pragma once

#include <vector>
#include "Complex.h"

class Region
{
public:

	std::vector<Complex> coefficients;
	std::vector<Complex> points;

	int N = 10;

	Complex CA;

	void AddCoefficient(const Complex c);

	void SetPoints(const int N);

	Complex w(const Complex z) const;

	Complex phi(const Complex z) const;

};

