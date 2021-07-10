#pragma once

#include "Fractal.h"

Fractal::Fractal(int it, double bail, Box bounds) : iterations(it), bailout(bail), bounds(bounds)
{
	SetCoordinates();
}

Fractal::Fractal(int it, double bail) : iterations(it), bailout(bail)
{
	Load();
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
		for (Region* region : leja.regions)
		{
			S += ~region->Omega(q);
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
	//parameters
	std::ofstream parameters;
	parameters.open("data\\parameters.txt");
	for (Region* region : leja.regions)
	{
		parameters << region->N << "," << region->s << "," << region->C << std::endl;
	}

	//leja
	for (int i = 0; i < leja.regions.size(); i++)
	{
		std::vector<Complex>& points = leja.regions.at(i)->points;
		std::ofstream file;
		file.open("data\\leja\\segment_" + std::to_string(i) + ".txt");
		for (Complex& p : points)
		{
			file << p.string() << std::endl;
		}
		file.close();
	}

	//coeff
	for (int i = 0; i < leja.regions.size(); i++)
	{
		std::vector<Complex>& coeff = leja.regions.at(i)->coeff;
		std::ofstream file;
		file.open("data\\coeff\\segment_" + std::to_string(i) + ".txt");
		for (Complex& c : coeff)
		{
			file << c.string() << std::endl;
		}
		file.close();
	}

	//bounds
	std::ofstream BoundsFile;
	BoundsFile.open("data\\bounds.txt");
	BoundsFile << bounds.x0 << std::endl;
	BoundsFile << bounds.y0 << std::endl;
	BoundsFile << bounds.x1 << std::endl;
	BoundsFile << bounds.y1 << std::endl;
	BoundsFile.close();
}

void Fractal::Load()
{
	str line;
	//parameters
	std::ifstream parameters;
	parameters.open("data\\parameters.txt");
	for (int i = 0; std::getline(parameters, line); i++)
	{
		deq d = split(line, ',');
		try
		{
			int N = std::stoi(d.at(0));
			double s = std::stod(d.at(1));
			leja.regions.at(i)->s = s;
			leja.regions.at(i)->SetN(N); //SetC
		}
		catch (const std::exception& e)
		{
		}
	}

	//bounds
	std::ifstream BoundsFile;
	BoundsFile.open("data\\bounds.txt");
	double x0 = 0, y0 = 0, x1 = 1, y1 = 1;
	try
	{
		std::getline(BoundsFile, line);
		x0 = std::stod(line);
		std::getline(BoundsFile, line);
		y0 = std::stod(line);
		std::getline(BoundsFile, line);
		x1 = std::stod(line);
		std::getline(BoundsFile, line);
		y1 = std::stod(line);
	}
	catch (const std::exception&)
	{
	}
	BoundsFile.close();
	bounds = Box(x0, y0, x1, y1);
	SetCoordinates();
}

void Fractal::SetCoordinates()
{
	double dx = (double)(bounds.Width()) / (double)p;
	double dy = (double)(bounds.Height()) / (double)p;

	for (int t = 0; t < pixels_size; t++)
	{
		coordinates[t].x = bounds.x0 + (t / p) * dx;
		coordinates[t].y = bounds.y0 + (t % p) * dy;
	}
}
