#pragma once

#include "Complex.h"
#include <vector>


class Region
{
	friend class Leja;

public:

	Region(std::vector<Complex>& boundary);

	Region(int N, double (*X)(double), double (*Y)(double));

	Region(std::vector<Complex>& leja);

	void SetN(int N);

	void AddN(int N);

	void setC(double s);

	Complex Omega(const Complex z) const;

private:

	std::vector<Complex> boundary;
	std::vector<Complex> leja;

	//the wanted size of Leja points, must be greater or equal to the size of the vector leja
	int N;
	double C = 1, s;

	double LejaDistance(Complex z) const;
};


