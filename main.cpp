
#define INTEGER_EXPONENT true
#define GRADIENT_DESCENT true

#include <cstdlib>
#include "Main.h"
#include "Trainer.h"

Fractal::Box bounds(-2, -2, 2, 2);
Fractal::Dist dist(-2, 2, -2, 2, -3, 5);
Trainer trainer(true, 0.30, 20, 10000, dist, bounds);

int main()
{
	test();

	//for (int i = 0; i < 10; i++)
	//{
	//	test();
	//}

	//while (true)
	//{
	//	std::cout << std::endl;
	//	for (int i = 0; i < Fractal::N; i++)
	//	{
	//		trainer.TrainPosOne(i);
	//	}
	//}

	return 0;
}

void test()
{
	trainer.GetPoles()[0] = Pole(-0.415733, 0.444055, -5);
	trainer.GetPoles()[1] = Pole(-1.413471, -0.143818, 0);
	trainer.GetPoles()[2] = Pole(1.710551, 1.352028, -2);
	trainer.GetPoles()[3] = Pole(-1.906499, -1.822334, 1);
	trainer.GetPoles()[4] = Pole(-1.194207, -0.628537, 4);
	trainer.GetPoles()[5] = Pole(-1.551590, -0.439766, 2);
	trainer.GetPoles()[6] = Pole(1.365934, -0.503206, 2);
	trainer.GetPoles()[7] = Pole(0.659970, 0.184494, 5);
	trainer.GetPoles()[8] = Pole(-0.814998, 0.210838, 5);
	trainer.GetPoles()[9] = Pole(-0.190373, -0.634208, 4);
	int M = 0;
	EXPONENT_TYPE& v = trainer.GetPoles()[M].m; //choose

	std::string s;
	for (int i = 0;; i++)
	{
		std::ifstream pot("data/coords_" + std::to_string(i) + ".csv");
		if (!pot.good())
		{
			s = std::to_string(i) + ".csv";
			break;
		}
	}
	std::ofstream coords;
	coords.open("data/coords_" + s);
	std::ofstream costs;
	costs.open("data/costs_" + s);
	std::ofstream ders;
	ders.open("data/ders_" + s);

	for (v = -10; v <= 10; v += 1)
	{
		trainer.Iterate();
		double cost = trainer.Cost();
		//double der = f.PosDerivative(M).x; //position
		double der = trainer.ExponentDerivative(M, cost); //exponent
		std::cout << v << "\t " << cost << std::endl;
		coords << v << std::endl;
		costs << cost << std::endl;
		ders << der << std::endl;
	}
	coords.close();
	costs.close();
	ders.close();
}