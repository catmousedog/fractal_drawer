#include "Region.h"

#pragma once

#define PI 3.1415926

Region::Region(std::vector<Complex>& leja, int N, double s) : leja(leja)
{
	SetN(N);
	SetC(s);
}

Region::Region(std::vector<Complex>& coeff, double s)
{
	int B = 10000;
	int C = coeff.size();
	for (int b = 0; b < B; b++)
	{
		double t = b / (double)B;
		Complex point;
		for (int c = 0; c < C; c++)
		{
			point += coeff[c] * Complex(2 * PI * (C / 2 - c) * t);
		}
		boundary.push_back(point);
	}
	leja.push_back(boundary.front());
	N = 1;
	SetC(s);
}

void Region::SetN(int N)
{
	if (N > leja.size())
	{
		AddN(N - leja.size());
	}
	this->N = N;
	SetC(s);
}

void Region::AddN(int N)
{
	for (int i = 0; i < N; i++)
	{
		double max = -1;
		Complex out;
		for (Complex& b : boundary)
		{
			double m = LejaDistance(b);
			if (m > max)
			{
				max = m;
				out = b;
			}
		}
		leja.push_back(out);
	}
	this->N += N;
	SetC(s);
}

void Region::SetC(double s)
{
	this->s = s;
	C = exp(-(signed int)leja.size() * s / 2.0);
	double prod = 1;
	Complex last = leja.back();
	for (int i = 0; i < N - 1; i++)
	{
		prod *= sqrt((last - leja.at(i)).AbsSquared());
	}
	C /= prod;
}

Complex Region::Omega(const Complex q) const
{
	Complex R(1, 0);
	for (int i = 0; i < N; i++)
	{
		R *= q - leja.at(i);
	}
	R *= C;
	return R;
}

double Region::LejaDistance(Complex q) const
{
	double prod = 1.0;
	for (Complex c : leja)
	{
		prod *= sqrt((q - c).AbsSquared());
	}
	return prod;
}
