
#define INTEGER_EXPONENT true

#include <cstdlib>
#include "main.h"
#include "Fractal.h"

Fractal::Box bounds(-2, -2, 2, 2);
Fractal::Dist dist(-2, 2, -2, 2, -3, 5);
Fractal f(20, 10000, dist, bounds);

void test();

int main()
{
	ForceDownhill = true;
	MinCost = 0.30;

	f.Randomize(1);

	f.Func(Complex(6, 3));

	f.Iterate();
	std::cout << f.Cost();
	f.Print();

	//test();

	//for (int i = 0; i < 10; i++)
	//{
	//	test();
	//}


	//while (true)
	//{
	//	std::cout << std::endl;
	//	for (int i = 0; i < Fractal::N; i++)
	//	{
	//		TrainPosOne(i);
	//	}
	//}
	return 0;
}

void test()
{
	f.GetPoles()[0] = Pole(-0.415733, 0.444055, -5);
	f.GetPoles()[1] = Pole(-1.413471, -0.143818, 0);
	f.GetPoles()[2] = Pole(1.710551, 1.352028, -2);
	f.GetPoles()[3] = Pole(-1.906499, -1.822334, 1);
	f.GetPoles()[4] = Pole(-1.194207, -0.628537, 4);
	f.GetPoles()[5] = Pole(-1.551590, -0.439766, 2);
	f.GetPoles()[6] = Pole(1.365934, -0.503206, 2);
	f.GetPoles()[7] = Pole(0.659970, 0.184494, 5);
	f.GetPoles()[8] = Pole(-0.814998, 0.210838, 5);
	f.GetPoles()[9] = Pole(-0.190373, -0.634208, 4);
	EXPONENT_TYPE& v = f.GetPoles()[0].m; //choose
	v = -4;
	f.Print();

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

	for (int i = 0; v <= 5; v += 1)
	{
		f.Iterate();
		double cost = f.Cost();
		//double der = f.PosDerivative(i).x; //position
		//double der = f.PowerDerivative(i); //exponent
		std::cout << v << "\t " << cost << std::endl;
		coords << v << std::endl;
		costs << cost << std::endl;
		//ders << der << std::endl;
	}
	coords.close();
	costs.close();
	ders.close();
}

void TrainPosOne(int i)
{
	std::cout << "TrainPosOne " << i << std::endl;
	double cost = f.Randomize(10);

	std::cout << "Randomize: " << cost << std::endl;

	double new_cost = -1.0;
	for (int j = 0;; j++)
	{
		new_cost = f.PosMinimize(i, cost, ForceDownhill);
		// could not find downhill step
		if (new_cost < 0)
		{
			std::cout << "could not take downhill step" << std::endl;
			break;
		}
		// downhill step
		else if (new_cost < cost)
		{
			cost = new_cost;
			std::cout << j << "\t downhill: " << new_cost << std::endl;
		}
		// non-downhill step
		else
		{
			cost = new_cost;
			std::cout << j << "\t uphill: " << new_cost << std::endl;
		}
	}
	//check if previous cost can be printed as new_cost is -1.0
	if (cost < MinCost)
	{
		std::cout << "printing" << std::endl;
		f.Print();
	}
}

void TrainPosAll()
{

}

void TrainPowerOne()
{}

void TrainPowerAll() {}

void TrainAllOne() {}

void TrainAllAll() {}

/**
void Train(int random, bool downhill, int limit, double cost)
{
	while (true)
	{
		std::cout << "next" << std::endl;

		f->Randomize(random, Fractal::poles);

		for (int i = 0;; i++)
		{
			bool b = f->Cycle(downhill);
			if (!b)
				break;
			if (i > limit)
			{
				f->Print();
				std::cout << "limit exceeded" << std::endl;
				break;
			}
		}
		if (f->Cost() < cost)
		{
			f->Print();
		}
	}
}

void FindMinimum(int random, bool downhill, int limit, double min_cost)
{
	while (true)
	{
		std::cout << "next" << std::endl;

		f->Randomize(random, Fractal::poles);

		for (int i = 0;; i++)
		{
			bool b = f->Cycle(downhill);
			if (!b)
				break;
			if (i > limit)
			{
				std::cout << "limit exceeded" << std::endl;
				break;
			}
		}
		double cost = f->Cost();
		if (cost < min_cost)
		{
			min_cost = cost;
			f->Print();
		}

	}
}

void Walk(int random, bool downhill, int limit)
{
	f->Randomize(random, Fractal::poles);

	for (int i = 0; i < limit; i++)
	{
		std::cout << limit-i << ": ";
		if (!f->Cycle(downhill))
			break;
	}
	f->Print();
}

void FindRandom(int random, double cost)
{
	while (true)
	{
		std::cout << "next" << std::endl;

		f->Randomize(random, Fractal::poles);

		if (f->Cost() < cost)
		{
			std::cout << "printing" << std::endl;
			f->Print();
		}
	}
}

void Benchmark(int M)
{
	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < M; i++)
	{
		std::cout << i << ", ";
		f->Iterate();
	}

	auto end = std::chrono::steady_clock::now();
	std::cout << "exec: " << (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count() << "ms\n";
}
**/