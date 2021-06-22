#pragma once

#include "Fractal.h"

Fractal::Fractal(int it, int bail, Box box) :
	iterations(it), bailout(bail), bounds(box), leja(), pixels()
{
	double dx = (double)(bounds.Width()) / (double)p;
	double dy = (double)(bounds.Height()) / (double)p;

	for (int t = 0; t < pixels_size; t++)
	{
		coordinates[t].x = bounds.x0 + (t / p) * dx;
		coordinates[t].y = bounds.y0 + (t % p) * dy;
	}
}

//Fractal function
void Fractal::Func(const int j, Complex q)
{
	for (int i = 0; i < iterations; i++)
	{
		if (q.AbsSquared() > bailout)
		{
			pixels[j] = (iterations - i) / (double)iterations;
			return;
		}

		/** f(z) **/
		Complex S(0, 0);
		for (Region& region : leja.regions)
		{
			S += ~region.Omega(q);
		}
		S = ~S;
		/**********/
		q *= S;
	}
	pixels[j] = 0.0;
}

void Fractal::SubIterate(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		Func(i, coordinates[i]);
	}
}

void Fractal::Iterate()
{
	//assign threads to their piece
	for (int i = 0; i < thread_count - 1; i++)
	{
		threads[i] = std::thread(&Fractal::SubIterate, this, ppt * i, ppt * (i + 1));
	}
	//final thread is a little bigger
	threads[thread_count - 1] = std::thread(&Fractal::SubIterate, this, ppt * (thread_count - 1), pixels_size);

	//wait for threads
	for (int i = 0; i < thread_count; i++)
	{
		threads[i].join();
	}
}

/*
void Fractal::Print()
{
	std::string s;
	for (int i = 0;; i++)
	{
		std::ofstream pot("data/pixels_" + std::to_string(i) + ".csv");
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
	for (Region& region : leja.regions)
	{
		par << std::endl;
		std::cout << std::endl;
		for (Complex p : region.leja)
		{
			str s = p.string();
			par << s << std::endl;
			std::cout << s << std::endl;
		}
	}
	par.close();
}
*/