#pragma once

#include "Complex.h"
#include <fstream>
#include <mutex>
#include <pch.h>

class Fractal2
{
protected:
	/* Variables */
	//constant used in the fractal function as e^C
	double C = 0;

	//constant used in top and bottom exponent
	TYPE tau = 1, beta = 1;

	//fractal properties
	int iterations, bailout;

public:
	//amount of poles
	static constexpr int T = 4, B = 0;

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

	/* Functions */

	//the fractal function
	inline double Func(Complex c) const;

	//iterates over all the pixels and assigns their value
	void Iterate();

	//print pixels and parameters to csv files
	void Print();

	/* Getters & Setters */
	Pole* GetTop() { return top; }

	Pole* GetBottom() { return bottom; }

	Complex* GetCoordinates() { return coordinates; }

	double* GetPixels() { return pixels; }

	TYPE GetTau() { return tau; }

	TYPE GetBeta() { return beta; }

	void SetTau(TYPE t) { tau = t; }

	void SetBeta(TYPE b) { beta = b; }


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

	//array of all values inside the bounds
	double pixels[pixels_size];

	//top poles
	Pole top[T];

	//bottom poles
	Pole bottom[B];

	/* Functions */
	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);

};


