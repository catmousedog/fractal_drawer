#include "Optimizer.h"
#include "Fractal2.h"
#include <pch.h>
#include <cmath>

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

int Optimizer::GradientE(int i)
{
	int& m = f.poles[i].m;
	int M = m;

	//E
	double E = energy, E1, E2;

	int grad = Max;
	int dist = 0;
	//stop if gradient is not an extremum or min_distance attempts were made
	while (dist <= min_distance && grad != Left && grad != Right)
	{
		dist++;

		//E1
		m = M - dist;
		f.Iterate();
		E1 = Energy();
		//E2
		m = M + dist;
		f.Iterate();
		E2 = Energy();

		grad = compare(E1, E, E2);
	}

	if (grad == Left)
	{
		//momentum
		double MomentumE;
		int i = 0;
		while (true) {
			m = M - dist - ++i;
			f.Iterate();
			MomentumE = Energy();
			if (MomentumE >= E1)
				break;
			if (i >= 2)
			{
				i++; //increase i by one so the second to last step was the current last step
				break;
			}

			E1 = MomentumE;
		}
		m = M; //reset
		return -dist - i + 1; //second to last step was downhill
	}
	else if (grad == Right)
	{
		//momentum
		double MomentumE;
		int i = 0;
		while (true) {
			m = M + dist + ++i;
			f.Iterate();
			MomentumE = Energy();
			if (MomentumE >= E2)
				break;
			if (i >= 2)
			{
				i++; //increase i by one so the second to last step was the current last step
				break;
			}

			E2 = MomentumE;
		}
		m = M; //reset
		return dist + i - 1; //second to last step was downhill
	}
	else if (grad == Min)
	{
		m = M; //reset
		return 0;
	}
	else if (grad == Max) //very unlikely
	{
		m = M; //reset
		//towards origin
		return -sgn(m) * min_distance;
	}
}

double Optimizer::OptimizeE(int& m, double E)
{
	int M = m;
	//E1
	m = M - 1;
	f.Iterate();
	double E1 = Energy();
	//E2
	m = M + 1;
	f.Iterate();
	double E2 = Energy();



	double Emin = std::min(std::min(E, E2), E1);
	if (Emin == E1)
	{
		m = M - 1;
		return E1;
	}
	else if (Emin == E2)
	{
		m = M + 1;
		return E2;
	}
	//check 2 further
	//E1
	m = M - 2;
	f.Iterate();
	E1 = Energy();
	//E2
	m = M + 2;
	f.Iterate();
	E2 = Energy();

	Emin = std::min(E1, std::min(E, E2));
	if (Emin == E1)
	{
		m = M - 2;
		return E1;
	}
	else if (Emin == E2)
	{
		m = M + 2;
		return E2;
	}

	m = M;
	return E;
}

double Optimizer::Energy()
{
	double sum = 0;
	for (int i = 0; i < Fractal2::pixels_size; i++)
	{
		double a = desired[i] - f.pixels[i];
		sum += a * a;
	}
	energy = sum;
	return sum;
}

