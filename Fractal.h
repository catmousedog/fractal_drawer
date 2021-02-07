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
	static constexpr int N = 2;
	//amount of pixels
	static constexpr int p = 200, pixels_size = p * p;
	static constexpr int thread_count = 100;
	//pixels per thread
	static constexpr int ppt = pixels_size / thread_count;

	//bounds in the complex plane
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

	//distributions used to randomize poles
	struct Dist
	{

		std::uniform_real_distribution<float> Distx;
		std::uniform_real_distribution<float> Disty;
		std::uniform_real_distribution<float> Distm;

		Dist(float mx, float Mx, float my, float My, float mm, float Mm) : Distx(mx, Mx), Disty(my, My), Distm(mm, Mm)
		{
		}
	};

	Fractal(int it, int bail, Dist dist, Box box);
	/* Functions */
	//randomize poles and return the minimal cost after given attempts
	float Randomize(int attempts);
	//the fractal function
	inline float Func(Complex c) const;
	//iterates over all the pixels and assigns their value
	void Iterate();
	//returns the total normalised energy of the current pixels
	float Cost();
	//returns the complex derivative of the position of the i'th' pole
	Complex PosDerivative(int i, float cost);
	//returns the real derivative of the exponent of the i'th' pole
	float PowerDerivative(int i, float cost);
	//does one training cycle for the position of the i'th' pole
	//returns the new_cost after the cycle: 
	//	new_cost < cost: the step was downhill
	//	new_cost >= cost: the step was not downhill and ForceDownhill was false (poles have changed)
	//	new_cost == -1.0f:  the step was not downhill and ForceDownhill was set true (poles haven't changed)
	float PosCycle(int i, float cost, bool ForceDownhill);
	//does one training cycle for the exponent of the i'th' pole
	//returns true if the step was downhill (New_Cost < Prev_Cost)
	//if ForceDownhill is set to true it will always take a step so that: New_Cost <= Prev_Cost
	bool PowerCycle(int i, float cost, bool ForceDownhill);
	//print pixels and parameters to csv files
	void Print();
	/* Getters & Setters */
	Pole* GetPoles() { return poles; }
private:

	/* Variables */

	//constant used in the fractal function as e^C
	const float C = 0;
	//amount of increasingly smaller steps taken to find an efficient step (lower cost)
	int cost_steps = 5;
	//stepsize to determine the positional derivative of the poles
	float pos_step = 0.01f;
	//stepsize to determine the exponent derivative of the poles
	float power_step = 0.01f;
	//randomizer
	std::mt19937 rng;
	//float distributions for poles
	Dist dist;
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

