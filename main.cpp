#pragma once

#include "Main.h"
#include "Drawer.h"
#include "Randomizer.h"

double a = 2;
Fractal2::Box bounds(-a, -a, a, a);
Fractal2 fractal(20, 10000, bounds);
Optimizer optimizer(fractal);
Drawer drawer(fractal, optimizer);
Randomizer random(fractal, optimizer, -2, 8);

int main()
{
	//ENERGY TEST
	//for (int i = 0; i < Fractal2::pixels_size; i++)
	//{
	//	double x = f.GetCoordinates()[i].x;
	//	double y = f.GetCoordinates()[i].y;
	//	if (x * x + y * y < 1)
	//		f.GetPixels()[i] = 1;
	//	else
	//		f.GetPixels()[i] = 0;
	//	
	//}
	//std::cout << op.NormEnergy() << std::endl;
	//return 0;

	//r(10);
	//f.out();
	//f.Iterate();
	//std::cout << op.NormEnergy() << std::endl;
	//d.Draw();

	//GRAPH
	//int& m = f.GetPoles()[2].m;
	//int M = 2;
	//int b = m - M;
	//m = b;
	//std::vector<double> x, y;
	//double E;
	//for (int i = 0; i < 2 * M + 1; i++)
	//{
	//	f.Iterate();
	//	E = op.NormEnergy();

	//	x.push_back((m - b) / double(2 * M));
	//	y.push_back(E);
	//	std::cout << x.at(i) << ", " << y.at(i) << std::endl;
	//	m++;
	//}
	//d.Graph(x, y, b, m, 0, 1);
	//return 0;

	Descend1(30, 0.0);

	return 0;
}

void Descend1(int M, double Emin)
{
	for (int a=0; a<25; a++)
	{
		std::cout << a << std::endl;
		//false if should be terminated
		bool running = true;
		//counter of how many times nothing changed, if equal to N => terminate
		int unchanged = 0;

		random(10);
		for (int i = 0; i < M && running; i++)
		{
			std::cout << M - i << std::endl;
			for (int j = 0; j < Fractal2::N && running; j++)
			{
				int& m = fractal.GetPoles()[j].m;
				int grad = optimizer.GradientE(j);

				if (grad != 0)
				{
					m += grad;
					unchanged = 0;
				}
				else
				{
					unchanged++;
				}
				fractal.Iterate();
				double NE = optimizer.NormEnergy(); //saves op.energy internally
				std::cout << NE << ", " << j << " += " << grad << std::endl;

				if (unchanged >= Fractal2::N)
					running = false;
			}
		}
		Print(optimizer.NormEnergy()); 
	}
}

void Print(double E)
{
	if (E < Emin)
	{
		fractal.Print();
		//drawer.Draw();
	}
}