#pragma once

#include "Complex.h"
#include <fstream>
#include <mutex>
#include <iostream>

class Fractal2
{
public:

	//amount of poles
	static constexpr int N = 10;

	//amount of pixels
	static constexpr int p = 200, pixels_size = p * p;

	//thread count
	static constexpr int thread_count = 80;

	//pixels per thread
	static constexpr int ppt = pixels_size / thread_count;

	//constant used in the fractal function as e^C
	double C = 0;

	//constant used in top and bottom exponent
	int tau = 1, beta = 1;

	//fractal properties
	int iterations, bailout;

	//temporary variable used during Iterate()
	int degree;

	//array of all the coordinates inside the bounds
	Complex coordinates[pixels_size];

	//array of all iterated values inside the bounds
	double pixels[pixels_size];

	//array of all potentials inside the bounds
	//double potential[pixels_size];

	//poles
	Pole poles[N];

	//distance per pixel
	double dx, dy;

	//bounds in the complex plane
	struct Box
	{
		double x0, y0, x1, y1;
		Box(double x0, double y0, double x1, double y1) : x0(x0), y0(y0), x1(x1), y1(y1)
		{
		}
		inline double Width()
		{
			return x1 - x0;
		}
		inline double Height()
		{
			return y1 - y0;
		}
	} bounds;

	Fractal2(int it, int bail, Box box);

	//the fractal function
	inline void Func(int i, Complex c);

	//iterates over all the pixels and assigns their value
	void Iterate();

	//print pixels and parameters to csv files
	void Print(double E);

	//cout
	void out(double E)
	{
		std::cout << E << std::endl;
		for (int i = 0; i < N; i++)
		{
			std::cout << poles[i].string() << std::endl;
		}
		std::cout << std::endl;
	}

	/* Getters & Setters */
	int GetDegree()
	{
		int d = 0;
		for (int i = 0; i < N; i++)
			d += poles[i].m;

		return d;
	}

private:
	//thread lock
	std::mutex mtx;

	//threads
	std::thread threads[thread_count];

	/* Functions */
	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);

	//friend class Drawer;
	//friend class Optimizer;
	//friend class Randomizer;
};


