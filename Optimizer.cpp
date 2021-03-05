#pragma once

#include "Optimizer.h"

Optimizer::Optimizer(Fractal2& f) : f(f), desired()
{
	//read from desired.csv and save the desired image
	std::ifstream des("desired.txt");
	std::string line;

	int t = 0;
	while (std::getline(des, line))
	{
		double v = std::stof(line);
		f.coordinates[t].x = f.bounds.x0 + (t / Fractal2::p) * f.dx;
		f.coordinates[t].y = f.bounds.y0 + (t % Fractal2::p) * f.dy;
		desired[t] = v;
		t++;
	}
	des.close();

	//normalistation
	norm = 1 / (double)Fractal2::pixels_size;
}

template<typename T>
T Optimizer::GradientC(T& c, T step)
{
	if (step == 0)
		return 0;

	double C = c;
	f.Iterate();
	double E = Energy(), E1, E2;

	int grad = Max;
	T dist = 0;
	//stop if gradient is not an extremum or min_distance attempts were made
	for (int i = 0; i < minimum_steps && grad != Left && grad != Right; i++)
	{
		dist += step;

		//E1
		c = C - dist;
		f.Iterate();
		E1 = Energy();
		//E2
		c = C + dist;
		f.Iterate();
		E2 = Energy();

		grad = compare(E1, E, E2);
	}

	if (grad == Left)
	{
		double MomentumE = 0.0;
		int j = 0;
		for (int i = 1; i < momentum_steps + 1; i++)
		{
			c = C - dist - (i * step);
			f.Iterate();
			MomentumE = Energy();
			if (MomentumE >= E1)
				break;
			j = i;
			E1 = MomentumE;
		}

		c = C; //reset
		return -dist - (j * step);
	}
	else if (grad == Right)
	{
		double MomentumE = 0.0;
		int j = 0;
		for (int i = 1; i < momentum_steps + 1; i++)
		{
			c = C + dist + (i * step);
			f.Iterate();
			MomentumE = Energy();
			if (MomentumE >= E2)
				break;
			j = i;
			E2 = MomentumE;
		}

		c = C; //reset
		return dist + j * step;
	}
	else if (grad == Min)
	{
		c = C; //reset
		return 0;
	}
	else if (grad == Max) //very unlikely
	{
		c = C; //reset
		//towards origin
		return (-sgn(c) * minimum_steps) * step;
	}
}

int Optimizer::GradientE(int i)
{
	return GradientC<int>(f.poles[i].m, stepm);
}

double Optimizer::GradientX(int i)
{
	return GradientC<double>(f.poles[i].x, stepx);
}

double Optimizer::GradientY(int i)
{
	return GradientC<double>(f.poles[i].y, stepy);
}

double Optimizer::Energy()
{
	double sum = 0;
	for (int i = 0; i < Fractal2::pixels_size; i++)
	{
		double a = desired[i] - f.pixels[i];
		if (f.pixels[i] < desired[i])
			a *= 0.6;
		sum += a * a;
	}
	return sum;
}

