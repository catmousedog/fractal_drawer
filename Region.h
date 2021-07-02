#pragma once

#include "Complex.h"
#include <vector>

class Region
{
public:

	//the wanted size of Leja points, must be greater or equal to the size of the vector leja
	int N;

	double s;

	std::vector<Complex> boundary;
	std::vector<Complex> leja;

	Region(std::vector<Complex> leja, int N, double s);

	Region(std::vector <Complex> coeff, const Complex offset, double s);

	Region(std::vector<Complex> coeff, const Complex offset, std::vector<Complex> leja, int N, double s);

	void SetN(int N);

	void AddN(int N);

	void SetC(double s);

	Complex Omega(const Complex z) const;

private:

	double C = 1;

	double LejaDistance(Complex z) const;

	void SetBoundary(std::vector<Complex> coeff, const Complex offset);
};


