#include "Optimizer.h"
#include <cmath>
//#include <algorithm>

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

	//for (int i = 0; i < Fractal2::pixels_size; i++)
	//{
	//	double x = f.coordinates[i].x;
	//	double y = f.coordinates[i].y;
	//	if (x * x + y * y < 1)
	//		desired[i] = 0.0;
	//	else
	//		desired[i] = 1.0;
	//}

	//normalistation
	norm = 1 / (double)Fractal2::pixels_size;
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
	//return sqrt(sum);
	return sum;
}

