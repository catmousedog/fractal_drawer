#pragma once

#include "main.h"

double a = 2;
Fractal2::Box bounds(-a, -a, a, a);
Fractal2 fractal(20, 10000, bounds);
Optimizer optimizer(fractal);
Drawer drawer(fractal);
Randomizer random(fractal, optimizer, -2, 8);

void test()
{
	std::cout << "test" << std::endl;
}

int main()
{
	//console commands
	typedef void (*fp)();
	std::map<std::string, fp> commands;
	commands.insert(std::pair<std::string, fp>("test", test));

	//pre console start


	while (true)
	{
		std::string cmd;
		std::cin >> cmd;
		if (commands.end() != commands.find(cmd))
		{
			fp f = commands[cmd];
			f();
		}

	}

	Descend1(30, 0.0);

	return 0;
}

void Descend1(int A, int M)
{
	for (int a = 0; a < A; a++)
	{
		std::cout << a << std::endl;
		//false if should be terminated
		bool running = true;
		//counter of how many times nothing changed, if equal to 3*N => terminate
		int unchanged = 0;

		random(10);
		Descend2(M);
		Print(optimizer.NormEnergy());
	}
}

void Descend2(int M)
{
	for (int i = 0; i < M; i++)
	{
		std::cout << M - i << std::endl;
		Descend3();
	}
}

void Descend3()
{
	for (int j = 0; j < Fractal2::N; j++)
	{
		//x
		double& x = fractal.GetPoles()[j].x;
		double gradx = optimizer.GradientX(j);
		if (gradx != 0)
			x += gradx;
		//y
		double& y = fractal.GetPoles()[j].y;
		double grady = optimizer.GradientY(j);
		if (grady != 0)
			y += grady;
		//exponent
		int& m = fractal.GetPoles()[j].m;
		int gradm = optimizer.GradientE(j);
		if (gradm != 0)
			m += gradm;
		//iterate
		fractal.Iterate();
		//NormEnergy() saves optimizer.energy internally so the Gradient can access it
		std::cout << optimizer.NormEnergy() << ", " << j << " += " << gradm << std::endl;
	}
}

void Print(double E)
{
	if (E < Emin)
	{
		fractal.Print();
		drawer.Draw();
	}
}

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
