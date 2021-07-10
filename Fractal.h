#pragma once

#include "leja.h"
#include <mutex>

class Fractal
{
public:

	//amount of pixels
	static constexpr int p = 1000, pixels_size = p * p;

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
		Box(double x, double y, double r)
		{
			x0 = x - r;
			x1 = x + r;
			y0 = y - r;
			y1 = y + r;
		}
		Box() : x0(0), y0(0), x1(1), y1(1)
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
		inline double CenterX()
		{
			return (x1 + x0) / 2.0;
		}
		inline double CenterY()
		{
			return (y1 + y0) / 2.0;
		}
		inline void Scale(double r)
		{
			double W = Width();
			double cx = CenterX();
			x0 = cx - r * W / 2.0;
			x1 = cx + r * W / 2.0;
			double H = Height();
			double cy = CenterY();
			y0 = cy - r * H / 2.0;
			y1 = cy + r * H / 2.0;
		}
		inline void Shift(Complex shift)
		{
			x0 += shift.x;
			x1 += shift.x;
			y0 += shift.y;
			y1 += shift.y;
		}
	} bounds;

	void SetCoordinates();

	Fractal(int it, double bail, Box box);

	Fractal(int it, double bail);

	//the fractal function
	void Func(int i, Complex c);

	//iterates over all the pixels and assigns their value
	void Iterate();

	void Save();

	void Load();

private:
	//thread lock
	std::mutex mtx;

	//threads
	std::thread threads[thread_count];

	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);

};


