#pragma once

#include "leja.h"
#include <mutex>

class Fractal
{
public:

	//amount of pixels
	static constexpr int p = 600, pixels_size = p * p;

	//thread count
	static constexpr int thread_count = 80;

	//pixels per thread
	static constexpr int ppt = pixels_size / thread_count;

	//fractal properties
	int iterations;

	double bailout;

	//coordinates inside the bounds in order
	Complex coordinates[pixels_size];

	//iterated values at coordinates in order
	double pixels[pixels_size];

	Leja leja;

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
		inline bool inside(double x, double y)
		{
			return x0 <= x && x <= x1 && y0 <= y && y <= y1;
		}
	} bounds;

	Fractal(int it, double bail, Box box);

	//the fractal function
	void Func(int i, Complex c);

	//iterates over all the pixels and assigns their value
	void Iterate();

	void Save();

private:
	//thread lock
	std::mutex mtx;

	//threads
	std::thread threads[thread_count];

	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);
};


