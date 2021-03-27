#pragma once

#include "Fractal2.h"
#include <cmath>

class Optimizer
{

private:

	//fractal
	Fractal& f;

	//inverse signed distance function
	double desired[Fractal::pixels_size];

	//normalisation constant
	double norm;

	//max steps it should look to find a lower energy if no minimum was found // [1, [
	int minimum_steps = 1;

	//max steps to take using momentum //[0, [
	int momentum_steps = 0;

	//stepsize exponent //[0, [
	int stepm = 1;

	//stepsize x //[0, [
	double stepx = 0.1;

	//stepsize y //[0, [
	double stepy = 0.1;

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

	void SetSteps(int min, int mom)
	{
		minimum_steps = min;
		momentum_steps = mom;
	}

	int GetMinSteps() { return minimum_steps; }

	int GetMomentumSteps() { return momentum_steps; }

	void SetStepSize(double x, double y, int m)
	{
		stepx = x;
		stepy = y;
		stepm = m;
	}

	double GetStepX() { return stepx; }

	double GetStepY() { return stepy; }

	int GetStepM() { return stepm; }

	double GetNorm() { return norm; }

	friend class Drawer;
};

