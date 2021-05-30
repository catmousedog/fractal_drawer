#pragma once

#include "Fractal.h"

#define PI 3.1415926
#define TAU 2*PI

// Constructs the fractal and reads from desired.csv
Fractal::Fractal(int it, int bail, Box box) :
	iterations(it), bailout(bail), bounds(box), lejas()
{
	double dx = (double)(bounds.Width()) / (double)p;
	double dy = (double)(bounds.Height()) / (double)p;

	for (int t = 0; t < pixels_size; t++)
	{
		coordinates[t].x = bounds.x0 + (t / p) * dx;
		coordinates[t].y = bounds.y0 + (t % p) * dy;
	}

	lejas.push_back(Leja(1000,
		[](double t) -> double
		{
			return cos(TAU * t);
		},
		[](double t) -> double
		{
			return -1 + 0.5 * sin(TAU * t) + 0.5 * cos(TAU * t);
		}));

	//lejas.push_back(Leja(1000,
	//	[](double t) -> double
	//	{
	//		return cos(TAU * t);
	//	},
	//	[](double t) -> double
	//	{
	//		return 1 - 0.5 * sin(TAU * t) - 0.5 * cos(TAU * t);
	//	}));
}

//Fractal function
inline void Fractal::Func(const int j, Complex q)
{
	for (int i = 0; i < iterations; i++)
	{
		if (q.AbsSquared() > bailout)
		{
			pixels[j] = (iterations - i) / (double)iterations;
			return;
		}

		Complex S(0, 0);
		/** f(z) **/
		for (Leja leja : lejas)
		{
			Complex R(1, 0);
			for (Complex p : leja.points)
			{
				R *= q - p;
			}
			R *= q;
			R *= leja.C;
			S += R;
		}
		/**********/
		q = S;
	}
	pixels[j] = 0.0;
}

inline void Fractal::SubIterate(int start, int end)
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

void Fractal::Print()
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
	for (Leja leja : lejas) {
		par << "LEJA" << std::endl;
		std::cout << "LEJA" << std::endl;
		for (Complex p : leja.points)
		{
			str s = p.string();
			par << s << std::endl;
			std::cout << s << std::endl;
		}
	}
	par.close();
}