#pragma once

#include "Pole.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include <random>

class Fractal
{
public:
	//amount of poles
	static constexpr int N = 40;
	//amount of pixels
	static constexpr int p = 200, pixels_size = p * p;
	static constexpr int thread_count = 100;
	//pixels per thread
	static constexpr int ppt = pixels_size / thread_count;

	struct Box
	{
		float x0, y0, x1, y1;
		Box(float x0, float y0, float x1, float y1) : x0(x0), y0(y0), x1(x1), y1(y1)
		{
		}
		inline float Width()
		{
			return x1 - x0;
		}
		inline float Height()
		{
			return y1 - y0;
		}
	};

	Fractal(int it, int bail, float m, float M, Box box);
	/* Functions */
	//randomize parameters
	//void Randomize(int attempts, int limit);
	//the fractal function
	inline float Func(Complex c) const;
	//applies the Iterator changing the pixels[] member
	void Iterate();
	//returns the sum of all energies for the current pixels[]
	float Cost();
	//returns the complex derivative of the 'i'th parameter
	Complex Derivative(int i, float cost);

	
	//does one training cycle and returns true if the Cycle was successful
	bool Cycle(bool ForceDownhill);
	//print pixels and parameters to csv files
	void Print();

	/* Getters & Setters */
	//Complex* GetParameters() { return parameters; }
	inline bool InCoordinates(float x, float y);
private:

	/* Variables */

	//constant used in the fractal function as e^C
	const float C = 0;
	int csteps = 5;
	float dstep = 0.01f, convergent_weight = 3.0f;
	//randomizers
	std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
	//thread lock
	std::mutex mtx;
	//threads
	std::thread threads[thread_count];
	//fractal properties
	int iterations, bailout;
	//distance per pixel
	float dx, dy;
	//area where the fractal is generated
	Box bounds;
	//array of all the coordinates inside the bounds
	Complex coordinates[pixels_size];

	//array of all values inside the bounds
	float pixels[pixels_size];

	//array of all desired values
	float desired[pixels_size];

	//poles, both numerator and denominator
	Pole poles[N];

	/* Functions */
	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);
};

