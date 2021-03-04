#pragma once

#include "Fractal2.h"

// Constructs the fractal and reads from desired.csv
Fractal2::Fractal2(int it, int bail, Box box) :
	iterations(it), bailout(bail), bounds(box)
{
	dx = (double)(bounds.Width()) / (double)p;
	dy = (double)(bounds.Height()) / (double)p;

	for (int t = 0; t < pixels_size; t++)
	{
		coordinates[t].x = bounds.x0 + (t / p) * dx;
		coordinates[t].y = bounds.y0 + (t % p) * dy;
	}

}

//Fractal function
inline void Fractal2::Func(const int j, Complex q)
{
	for (int i = 0; i < iterations; i++)
	{
		if (q.AbsSquared() > bailout)
		{
			pixels[j] = (iterations - i) / (double)iterations;
			potential[j] = 0.5 * log(q.AbsSquared()) * pow(degree, -i);
			return;
		}

		Complex R(1, 0);
		/** f(z) **/
		for (int j = 0; j < N; j++)
		{
			R *= poles[j].poly(q, tau);
		}
		R *= Complex(exp(C), 0);
		/****/

		q = R;
	}
	pixels[j] = 0.0;
	potential[j] = 0.5 * log(q.AbsSquared()) * pow(degree, -iterations);
}

inline void Fractal2::SubIterate(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		Func(i, coordinates[i]);
	}
}

void Fractal2::Iterate()
{
	degree = GetDegree();
	//assign threads to their piece
	for (int i = 0; i < thread_count - 1; i++)
	{
		threads[i] = std::thread(&Fractal2::SubIterate, this, ppt * i, ppt * (i + 1));
	}
	//final thread is a little bigger
	threads[thread_count - 1] = std::thread(&Fractal2::SubIterate, this, ppt * (thread_count - 1), pixels_size);

	//wait for threads
	for (int i = 0; i < thread_count; i++)
	{
		threads[i].join();
	}
}

void Fractal2::Print(double E)
{
	std::string s;
	for (int i = 0;; i++)
	{
		std::ifstream pot("data/pixels_" + std::to_string(i) + ".csv");
		if (!pot.good())
		{
			s = std::to_string(i) + ".csv";
			break;
		}
	}

	std::ofstream pix;
	pix.open("data/pixels_" + s);
	for (int i = 0; i < pixels_size; i++)
	{
		pix << pixels[i] << std::endl;
	}
	pix.close();

	std::ofstream par;
	par.open("data/parameters_" + s);
	par << E << std::endl;
	std::cout << E << std::endl;
	for (int i = 0; i < N; i++)
	{
		par << poles[i].string() << std::endl;
		std::cout << poles[i].string() << std::endl;
	}
	par.close();
}