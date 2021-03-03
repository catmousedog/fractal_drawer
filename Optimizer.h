#pragma once

#include "Fractal2.h"
#include "Util.h"
#include <cmath>

class Optimizer
{

private:

	//fractal
	Fractal2& f;

	//inverse signed distance function
	double desired[Fractal2::pixels_size];

	//step function constant, higher means closer to a step function
	double alpha = 1.0;

	//max steps it should look to find a lower energy if no minimum was found
	// [1, [
	int minimum_steps = 2;

	//max steps to take using momentum
	// [0, [
	int momentum_steps = 3;

	//normalisation constant
	double norm;

	//current energy when last calculated
	double energy = 0.0;

	//stepsizes
	int stepm = 1;
	double stepx = 0.1, stepy = 0.1;

	//gradient for coordinate
	template<typename T>
	T GradientC(T& c, T step);

public:

	Optimizer(Fractal2& f);

	double Energy();

	double NormEnergy() { return Energy() * norm; }

	int GradientE(int i);

	double GradientX(int i);

	double GradientY(int i);

	//tau
	void OptimizeT();

	//beta
	void OptimizeB();

	//to set energy without recalculating it
	void SetEnergy(double energy) { (*this).energy = energy; }

	void setSteps(int m, double x, double y)
	{
		stepm = m;
		stepx = x;
		stepy = y;
	}

	friend class Drawer;
};

