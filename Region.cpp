#include "Region.h"

#pragma once

#define PI 3.1415926

void Region::SetBoundary(std::vector<Complex> coeff, const Complex offset)
{
	int B = 10000;
	int C = coeff.size();
	for (int b = 0; b < B; b++)
	{
		double t = b / (double)B;
		Complex point;
		for (int c = 0; c < C; c++)
		{
			Complex z = coeff[c] * Complex(2 * PI * (C / 2 - c) * t);
			if (c == C / 2)
				z += offset;
			point += z;
		}
		boundary.push_back(point);
	}
}

Region::Region(std::vector<Complex> leja, int N, double s) : leja(leja)
{
	this->s = s;
	SetN(N);
}

Region::Region(std::vector<Complex> coeff, const Complex offset, double s)
{
	SetBoundary(coeff, offset);
	this->s = s;
	SetN(1);
}

Region::Region(std::vector<Complex> coeff, const Complex offset, std::vector<Complex> leja, int N, double s) : leja(leja)
{
	SetBoundary(coeff, offset);
	this->s = s;
	SetN(N);
}

void Region::SetN(int N)
{
	this->N = N;
	if (N > leja.size())
	{
		AddN(N - leja.size());
	}
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
}

void Region::SetC(double s)
{
	this->s = s;
	Complex last;
	if (N == 0)
	{
		return;
	}
	else
	{
		last = leja.at(N - 1);
	}
	C = exp(-N * s / 2.0);
	double prod = 1;
	for (int i = 0; i < N - 1; i++)
	{
		prod *= sqrt((last - leja.at(i)).AbsSquared());
	}
	C /= prod;
}

Complex Region::Omega(const Complex& q) const
{
	Complex R(1, 0);
	for (const Complex& l : leja)
	{
		R *= q - l;
	}
	return R * C;
}

double Region::LejaDistance(const Complex& q) const
{
	double prod = 1.0;
	for (const Complex& l : leja)
	{
		prod *= sqrt((q - l).AbsSquared());
	}
	return prod;
}
