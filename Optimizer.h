#pragma once

#include "Fractal2.h"

class Optimizer
{

private:

	//fractal
	Fractal2& f;

	//inverse signed distance function
	double isdf[Fractal2::pixels_size];

	//step function constant, higher means closer to a step function
	double alpha = 1.0;

	//normalisation constant
	double norm;

public:

	Optimizer(Fractal2& f);

	double Energy();

	double SDF(int i) { return isdf[i]; }

	double dEdC();

	double dEdT(int i);

	friend class Drawer;
};

