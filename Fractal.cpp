#pragma once

#include "Fractal.h"

// Constructs the fractal and reads from desired.csv
Fractal::Fractal(int it, int bail, Box box) : iterations(it), bailout(bail), bounds(box)
{
	double dx = (double)(bounds.Width()) / (double)p;
	double dy = (double)(bounds.Height()) / (double)p;

	for (int t = 0; t < pixels_size; t++)
	{
		coordinates[t].x = bounds.x0 + (t / p) * dx;
		coordinates[t].y = bounds.y0 + (t % p) * dy;
	}

	//read from image
	std::ifstream des(".csv");
	std::string line;

	//first line is amount of relevant pixels (not -1)
	std::getline(des, line);

	//total / relevant counter
	int t = 0, r = 0;
	while (std::getline(des, line))
	{
		float v = std::stof(line);
		if (v >= 0)
		{
			desired[r] = v;
			r++;
		}
		t++;
	}
	des.close();

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

		Complex R(1, 0);
		/** f(z) **/
		/**********/
		q = R;
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
	for (int i = 0; i < N; i++)
	{
		//par << poles[i].string() << std::endl;
		//std::cout << poles[i].string() << std::endl;
	}
	par.close();
}