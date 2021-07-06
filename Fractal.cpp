#pragma once

#include "Fractal.h"

Fractal::Fractal(int it, double bail, Box box) : iterations(it), bailout(bail), bounds(box), leja(), pixels()
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
		double z = q.AbsSquared();
		if (z > bailout || isnan(z))
		{
			pixels[j] = (iterations - i) / (double)iterations;
			return;
		}

		/** w(z) **/
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


void Fractal::Save()
{
	for (int i = 0; i < leja.regions.size(); i++)
	{
		std::ofstream file;
		file.open("data\\leja\\segment_" + std::to_string(i) + ".txt");
		for (Complex p : leja.regions.at(i).leja)
		{
			file << p.string() << std::endl;
		}
		file.close();
	}
	for (int i = 0; i < leja.regions.size(); i++)
	{
		std::ofstream file;
		file.open("data\\coeff\\segment_" + std::to_string(i) + ".txt");
		for (Complex c : leja.regions.at(i).coeff)
		{
			file << c.string() << std::endl;
		}
		file.close();
	}
}
