
#include <cstdlib>
#include "main.h"
#include "Fractal.h"

Fractal::Box bounds(-2, -2, 2, 2);
Fractal* f = new Fractal(80, 10000, -1, 1, bounds);

int main()
{
	//Train(200, false, 200, 0.5f);
	//FindMinimum(100, false, 1000, 0.5f);
	//Walk(1, false, 1000);
	//FindRandom(1000, 1.0f);
	//Benchmark(10);
	f->Func(Complex(1, 1));

	delete f;
	return 0;
}
/**
void Train(int random, bool downhill, int limit, float cost)
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

void FindMinimum(int random, bool downhill, int limit, float min_cost)
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
		float cost = f->Cost();
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

void FindRandom(int random, float cost)
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