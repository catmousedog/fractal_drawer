
#include <cstdlib>
#include "main.h"
#include "Fractal.h"

Fractal::Box bounds(-2, -2, 2, 2);
Fractal::Dist dist(-2, 2, -2, 2, -2, 5);
Fractal f(20, 10000, dist, bounds);

int main()
{
	ForceDownhill = true;
	MinCost = 0.30;



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