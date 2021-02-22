#include "Optimizer.h"
#include <iostream>
#include <cmath>

Optimizer::Optimizer(Fractal2& f) : f(f)
{
	//create inverse SDF
	for (int i = 0; i < Fractal2::pixels_size; i++)
	{
		double x = f.coordinates[i].x;
		double y = f.coordinates[i].y;
		isdf[i] = 1 / (sqrt(x * x + y * y) - 1);
	}
	//normalisation
	norm = 0;
	for (int i = 0; i < Fractal2::p; i++)
	{
		norm += abs(isdf[i]);
	}
	norm = 1 / norm;
}

double Optimizer::Energy()
{
	double sum = 0;
	for (int i = 0; i < Fractal2::p; i++)
	{
		sum += -tanh(alpha * f.potential[i]) * isdf[i];
	}
	return sum * norm;
}

double Optimizer::dEdC()
{
	double sum = 0;
	for (int i = 0; i < Fractal2::pixels_size; i++)
	{
		double a = cosh(f.potential[i] * alpha);
		sum += alpha * isdf[i] / (a * a);
	}
	return sum * norm;
}

double Optimizer::dEdT(int i)
{
	return 0;
}