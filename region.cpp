#include "region.h"
#include <iostream>

#define PI 3.1415926
#define TAU 2*PI
#define C 2
//#define C coefficients.size() / 2

void Region::AddCoefficient(Complex c)
{
	coefficients.push_back(c);
	SetPoints(N);
}

void Region::SetPoints(const int N)
{
	this->N = N;
	points.clear();
	for (double t = 0; t < TAU; t += TAU / (double)N)
	{
		points.push_back(phi(Complex(t)));
	}
	if (coefficients.size() > C-1)
		CA = coefficients[C-1] ^ (-N);
}

Complex Region::phi(const Complex z) const
{
	Complex sum(0, 0);
	for (int i = 0; i < coefficients.size(); i++)
	{
		sum += coefficients[i] * (z ^ (C - i));
	}
	return sum;
}

Complex Region::w(const Complex z) const
{
	Complex prod(1, 0);
	for (int i = 0; i < N; i++)
	{
		prod *= z - points[i];
	}
	return prod * CA + Complex(1, 0);
}

void Region::setCA(const Complex CA)
{
	this->CA = CA;
}