#include "leja.h"

#define PI 3.1415926
#define TAU 2*PI

Leja::Leja()
{
	auto X1 = [](double t) -> double
	{
		return pow(sin(TAU * t), 3.0);
	};
	auto Y1 = [](double t) -> double
	{
		return cos(TAU * t) - cos(2 * TAU * t);
	};
	addBoundary(1000, X1, Y1);

	auto X2 = [](double t) -> double
	{
		return cos(TAU * t);
	};
	auto Y2 = [](double t) -> double
	{
		return -4 + sin(TAU * t) - 0.5 * cos(TAU * t);
	};
	addBoundary(1000, X2, Y2);

	points.push_back(boundary.front());
}

void Leja::addBoundary(int N, double (*X)(double), double (*Y)(double))
{
	for (int i = 0; i < N; i++)
	{
		double t = i / (double)N;
		boundary.push_back(Complex(X(t), Y(t)));
	}
}

void Leja::add(int N)
{
	for (int i = 0; i < N; i++)
	{
		double max = -1;
		Complex out(0, 0);
		for (Complex c : boundary)
		{
			double m = func(c);
			if (m > max)
			{
				max = m;
				out = c;
			}
		}
		points.push_back(out);
	}
	setConstant();
}

void Leja::setConstant()
{
	C = exp(-(signed int)points.size() * s / 2.0);
	double prod = 1;
	Complex last = points.back();
	for (int i = 0; i < points.size() - 1; i++)
	{
		prod *= sqrt((last - points.at(i)).AbsSquared());
	}
	C /= prod;
}

double Leja::func(Complex z)
{
	double prod = 1.0;
	for (Complex c : points)
	{
		prod *= sqrt((z - c).AbsSquared());
	}
	return prod;
}