#pragma once

#include "Complex.h"
#include <fstream>
#include <mutex>
#include <pch.h>
#include <iostream>

class Fractal2
{
private:
	//constant used in the fractal function as e^C
	double C = 0;

	//constant used in top and bottom exponent
	int tau = 1, beta = 1;

	//fractal properties
	int iterations, bailout;

	//temporary variable used during Iterate()
	int degree;

public:
	//amount of poles
	static constexpr int N = 20;

	//amount of pixels
	static constexpr int p = 200, pixels_size = p * p;

	//thread count
	static constexpr int thread_count = 100;

	//pixels per thread
	static constexpr int ppt = pixels_size / thread_count;

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
	};

	Fractal2(int it, int bail, Box box);

	//the fractal function
	inline void Func(int i, Complex c);

	//iterates over all the pixels and assigns their value
	void Iterate();

	//print pixels and parameters to csv files
	void Print();

	//cout
	void out()
	{
		for (int i = 0; i < N; i++)
		{
			std::cout << "test(" << poles[i].string() << ");" << std::endl;
		}
		std::cout << std::endl;
	}

	/* Getters & Setters */
	Pole* GetPoles() { return poles; }

	Complex* GetCoordinates() { return coordinates; }

	double* GetPixels() { return pixels; }

	int GetDegree()
	{
		int d = 0;
		for (int i = 0; i < N; i++)
			d += poles[i].m;

		return d;
	}

	double& GetC() { return C; }
	int& GetTau() { return tau; }
	int& GetBeta() { return beta; }

private:
	//distance per pixel
	double dx, dy;

	//area where the fractal is generated
	Box bounds;

	//thread lock
	std::mutex mtx;

	//threads
	std::thread threads[thread_count];

	//array of all the coordinates inside the bounds
	Complex coordinates[pixels_size];

	//array of all iterated values inside the bounds
	double pixels[pixels_size];

	//array of all potentials inside the bounds
	double potential[pixels_size];

	//top poles
	Pole poles[N];

	/* Functions */
	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);

	friend class Drawer;
	friend class Optimizer;
	friend class Randomizer;
};


