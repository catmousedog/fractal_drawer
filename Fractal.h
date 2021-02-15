#pragma once

#include "Complex.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include <random>

#ifndef GRADIENT_DESCENT
#define GRADIENT_DESCENT true
#endif

class Fractal
{
public:
	//amount of poles
	static constexpr int N = 10;
	//amount of pixels
	static constexpr int p = 200, pixels_size = p * p;
	static constexpr int thread_count = 100;
	//pixels per thread
	static constexpr int ppt = pixels_size / thread_count;
	//position epsilon: the smallest stepsize for the position of the poles
	const double pos_eps = 4.51E13 * std::numeric_limits<double>::epsilon();
	Vector pos_eps_vec = Vector(pos_eps, pos_eps);
	//exponent epsilon: the smallest stepsize for the exponent of the poles
#if INTEGER_EXPONENT
	const int exponent_eps = 1;
#else
	const double exponent_eps = 4.51E13 * std::numeric_limits<double>::epsilon();
#endif

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
	//distributions used to randomize poles
	struct Dist
	{

		double mx, Mx;
		std::uniform_real_distribution<double> Distx;
		double my, My;
		std::uniform_real_distribution<double> Disty;
#if INTEGER_EXPONENT
		int mm, Mm;
		std::uniform_int_distribution<int> Distm;
#else
		double mm, Mm;
		std::uniform_real_distribution<double> Distm;
#endif


		Dist(double mx, double Mx, double my, double My, EXPONENT_TYPE mm, EXPONENT_TYPE Mm) : Distx(mx, Mx), Disty(my, My), Distm(mm, Mm)
		{
			this->mx = mx;
			this->Mx = Mx;
			this->my = my;
			this->My = My;
			this->mm = mm;
			this->Mm = Mm;
		}
		Dist(const Dist& dist) : Distx(dist.mx, dist.Mx), Disty(dist.my, dist.My), Distm(dist.mm, dist.Mm)
		{
			mx = dist.mx;
			Mx = dist.Mx;
			my = dist.my;
			My = dist.My;
			mm = dist.mm;
			Mm = dist.Mm;
		}
	};

	Fractal(int it, int bail, Dist dist, Box box);
	/* Functions */
	//randomize poles and return the minimal cost after given attempts
	double Randomize(int attempts);
	//the fractal function
	inline double Func(Complex c) const;
	//iterates over all the pixels and assigns their value
	void Iterate();
	//returns the total normalised energy of the current pixels
	double Cost();
	//returns the complex derivative of the position of the i'th' pole
	//returns 0 if the current position is in a minimum
	Vector PosDerivative(int i, double cost);
	//returns the real derivative of the exponent of the i'th' pole
	//returns 0 if the current exponent is in a minimum
	double ExponentDerivative(int i, double cost);
	//print pixels and parameters to csv files
	void Print();
	/* Getters & Setters */
	Pole* GetPoles() { return poles; }

protected:
	/* Variables */
	//constant used in the fractal function as e^C
	const double C = 0;
	//amount of increasingly smaller steps taken to find an efficient step (lower cost)
	int cost_steps = 5;
	//stepsize to determine the positional derivative of the poles
	double pos_step = 0.01;
	//stepsize to determine the exponent derivative of the poles
	double power_step = 0.01;
	//randomizer
	std::mt19937 rng;
	//double distributions for poles
	Dist dist;
	//thread lock
	std::mutex mtx;
	//threads
	std::thread threads[thread_count];
	//fractal properties
	int iterations, bailout;
	//distance per pixel
	double dx, dy;
	//area where the fractal is generated
	Box bounds;
	//array of all the coordinates inside the bounds
	Complex coordinates[pixels_size];
	//array of all values inside the bounds
	double pixels[pixels_size];
	//array of all desired values
	double desired[pixels_size];
	//poles, both numerator and denominator
	Pole poles[N];
	/* Functions */
	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);
};

