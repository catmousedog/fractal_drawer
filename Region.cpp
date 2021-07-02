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
