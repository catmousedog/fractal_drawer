#pragma once

#include "Drawer.h"
#include <iostream>

double a = 2;
Fractal2::Box bounds(-a, -a, a, a);
Fractal2 f(50, 10000, bounds);
Optimizer op(f);
Drawer drawer(f, op);

int main()
{

	f.GetTop()[0] = Top(0, 0, 2);
	f.GetTop()[1] = Top(-1, -1, 2);
	f.GetTop()[2] = Pole(1, 1, 2);
	//f.GetTop()[3] = Pole(-1.551590, -0.439766, 2);
	//f.GetTop()[4] = Pole(1.365934, -0.503206, 2);
	//f.GetTop()[5] = Pole(0.659970, 0.184494, 5);
	//f.GetTop()[6] = Pole(-0.814998, 0.210838, 5);
	//f.GetTop()[7] = Pole(-0.190373, -0.634208, 4);
	//f.GetBottom()[0] = Bottom(1, 1, -1);
	//f.GetBottom()[1] = Pole(-0.415733, 0.444055, -5);

	f.Iterate();

	std::cout << op.Energy() << std::endl;
	std::cout << op.dEdC() << std::endl;
	drawer.Draw();

	double& c = f.GetC();
	std::vector<double> x, y;

	double cmin = 1;
	double cmax = 3;
	double n = 100;
	double step = (cmax - c) / n;
	c = cmin;
	for (int i = 0; c < cmax; i++)
	{
		f.Iterate();
		x.push_back(i / (double)n);
		y.push_back(op.Energy());
		//drawer.Draw();
		c += step;
	}

	drawer.Graph(x, y, cmin, cmax);

	return 0;
}

//void test()
//{
//	trainer.GetPoles()[0] = Pole(-0.415733, 0.444055, -5);
//	trainer.GetPoles()[1] = Pole(-1.413471, -0.143818, 0);
//	trainer.GetPoles()[2] = Pole(1.710551, 1.352028, -2);
//	trainer.GetPoles()[3] = Pole(-1.906499, -1.822334, 1);
//	trainer.GetPoles()[4] = Pole(-1.194207, -0.628537, 4);
//	trainer.GetPoles()[5] = Pole(-1.551590, -0.439766, 2);
//	trainer.GetPoles()[6] = Pole(1.365934, -0.503206, 2);
//	trainer.GetPoles()[7] = Pole(0.659970, 0.184494, 5);
//	trainer.GetPoles()[8] = Pole(-0.814998, 0.210838, 5);
//	trainer.GetPoles()[9] = Pole(-0.190373, -0.634208, 4);
//	int M = 0;
//	EXPONENT_TYPE& v = trainer.GetPoles()[M].m; //choose
//
//	std::string s;
//	for (int i = 0;; i++)
//	{
//		std::ifstream pot("data/coords_" + std::to_string(i) + ".csv");
//		if (!pot.good())
//		{
//			s = std::to_string(i) + ".csv";
//			break;
//		}
//	}
//	std::ofstream coords;
//	coords.open("data/coords_" + s);
//	std::ofstream costs;
//	costs.open("data/costs_" + s);
//	std::ofstream ders;
//	ders.open("data/ders_" + s);
//
//	for (v = -10; v <= 10; v += 1)
//	{
//		trainer.Iterate();
//		double cost = trainer.Cost();
//		//double der = f.PosDerivative(M).x; //position
//		double der = trainer.ExponentDerivative(M, cost); //exponent
//		std::cout << v << "\t " << cost << std::endl;
//		coords << v << std::endl;
//		costs << cost << std::endl;
//		ders << der << std::endl;
//	}
//	coords.close();
//	costs.close();
//	ders.close();
//}