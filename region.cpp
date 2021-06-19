#include "region.h"

#define PI 3.1415926
#define TAU 2*PI

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
	CA = coefficients[0] ^ (-N);
	//CA = Complex(1, 0);
}

Complex Region::phi(const Complex z) const
{
	Complex sum(0, 0);
	for (int i = 0; i < coefficients.size(); i++)
	{
		sum += coefficients[i] * (z ^ (1.0 - (double)i));
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
