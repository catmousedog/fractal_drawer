#pragma once

#include <vector>
#include <fstream>
#include "Complex.h"

class Leja
{
public:

	std::vector<Complex> boundary;
	std::vector<Complex> points;

	double C = 1.0;

	double s = 0.3;

	Leja(int N, double (*X)(double), double(*Y)(double));

	void add(int N);

	void setConstant();

private:

	double func(Complex z);

};

