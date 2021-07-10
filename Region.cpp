#include "Region.h"

#pragma once

#define PI 3.1415926

void Region::SetBoundary()
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
}

Region::Region(std::vector<Complex> leja, int N, double s) : points(leja)
{
	this->s = s;
	SetN(N);
}

Region::Region(std::vector<Complex> coeff, double s) : coeff(coeff)
{
	SetBoundary();
	this->s = s;
	SetN(1);
}

Region::Region(std::vector<Complex> coeff, std::vector<Complex> leja, int N, double s) : points(leja), coeff(coeff)
{
	SetBoundary();
	this->s = s;
	SetN(N);
}

void Region::SetN(int N)
{
	if (N > points.size())
	{
		this->N = points.size();
	}
	else
	{
		this->N = N;
	}
	SetC(s);
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
		last = points.at(N - 1);
	}
	C = exp(-N * s / 2.0);
	double prod = 1;
	for (int i = 0; i < N - 1; i++)
	{
		prod *= sqrt((last - points.at(i)).AbsSquared());
	}
	C /= prod;
}

Complex Region::Omega(const Complex& q) const
{
	Complex R(1, 0);
	for (int i = 0; i < N; i++)
	{
		R *= q - points.at(i);
	}
	return R * C;
}

void Region::CalculateLeja(int i)
{
	AddN(200);
	std::ofstream LejaFile;
	LejaFile.open(GetPathLeja(i));
	for (Complex& l : points)
	{
		LejaFile << l.string() << std::endl;
	}
	LejaFile.close();
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
		points.push_back(out);
	}
}

double Region::LejaDistance(const Complex& q) const
{
	double prod = 1.0;
	for (const Complex& l : points)
	{
		prod *= sqrt((q - l).AbsSquared());
	}
	return prod;
}