#pragma once

#include "Fractal2.h"

class Optimizer
{

private:

	//fractal
	Fractal2& f;

	//inverse signed distance function
	double desired[Fractal2::pixels_size];

	//step function constant, higher means closer to a step function
	double alpha = 1.0;

	//amount of steps it should take around a minimum to find another lower minimum
	//also applies to maximum, in the latter a step is always taken
	int min_distance = 2;

	//normalisation constant
	double norm;

	//current energy when last calculated
	double energy = 0.0;

public:

	Optimizer(Fractal2& f);

	double Energy();

	double NormEnergy() { return Energy() * norm; }

	//returns the optimal step that needs to be taken for the i'th' exponent
	//the op.energy is ambigious after calling this method
	int GradientE(int i);

	//optimize the given exponent also takes the energy of the current state
	//if a more optimal exponent was found it will be changed to that value
	//but Iterate will not have been called
	//returns the energy of the new state
	double OptimizeE(int& m, double E);

	//tau
	void OptimizeT();

	//beta
	void OptimizeB();

	friend class Drawer;
};

