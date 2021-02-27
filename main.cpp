#pragma once

#include "Drawer.h"
#include "Randomizer.h"

double a = 2;
Fractal2::Box bounds(-a, -a, a, a);
Fractal2 f(20, 10000, bounds);
Optimizer op(f);
Drawer d(f, op);
Randomizer r(f, op, -2, 8);

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

	double M = 30;
	//OPTIMIZE
	while (true)
	{
		r(10);
		f.Iterate();
		double E = op.Energy();
		//counter of how many times nothing changed, if equal to N => terminate
		int terminate = 0;
		for (int i = 0; i < M; i++)
		{
			std::cout << M - i << std::endl << std::endl;
			for (int j = 0; j < Fractal2::N; j++)
			{
				int& m = f.GetPoles()[j].m;
				int M = m;
				E = op.OptimizeE(m, E);
				f.Iterate();
				if (m - M == 0)
					terminate++;
				else
					terminate = 0;
				std::cout << E / double(Fractal2::pixels_size) << ", " << j << " += " << m - M << std::endl;

				if (terminate == Fractal2::N)
					break;
			}
			if (terminate == Fractal2::N)
				break;
		}
		//if (E < 0.05)
		//{
			f.out();
			f.Print();
			d.Draw();
		//}
	}

	return 0;
}

