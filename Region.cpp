#include "Region.h"

#pragma once

Region::Region(std::vector<Complex>& leja, int N, double s) : leja(leja)
{
	if (N <= leja.size())
		this->N = N;
	else
		this->N = leja.size();
	setC(s);
}

void Region::SetN(int N)
{
	if (N <= leja.size())
		this->N = N;
	else
		this->N = leja.size();
	setC(s);
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
	N++;
	setC(s);
}

void Region::setC(double s)
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

Complex Region::Omega(const Complex z) const
{
	Complex R(1, 0);
	for (int i = 0; i < N; i++)
	{
		R *= z - leja.at(i);
	}
	R *= C;
	return R;
}

double Region::LejaDistance(Complex z) const
{
	double prod = 1.0;
	for (Complex c : leja)
	{
		prod *= sqrt((z - c).AbsSquared());
	}
	return prod;
}
