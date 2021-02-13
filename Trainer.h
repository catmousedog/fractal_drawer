#pragma once

#include "Fractal.h"

class Trainer : public Fractal
{
public:
	//whether the steps should always be forced downhill or not at all
	bool ForceDownhill;
	//the minimum cost before the poles can be worth wile saving
	double MinCost;

	Trainer(bool ForceDownhill, double MinCost, int it, int bail, Dist dist, Box box) : 
		Fractal(it, bail, dist, box), ForceDownhill(ForceDownhill), MinCost(MinCost)
	{
	}

	//train the position of one pole
	void TrainPosOne(int i);
	//train the position of all poles
	void TrainPosAll();
	//train the exponent of one pole
	void TrainPowerOne();
	//train the exponenet of all poles
	void TrainPowerAll();
	//train both the position and exponent of one pole
	void TrainAllOne();
	//train both the position and exponent of all poles
	void TrainAllAll();
	//takes one step for the position of the i'th' pole
	//returns the new_cost after the step: 
	//	new_cost < cost: the step was downhill
	//	new_cost >= cost: the step was non-downhill (ForceDownhill was false and the poles have changed)
	//	new_cost == -1.0f:  no downhill step could be taken (ForceDownhill was set true and the poles haven't changed)
	double PosMinimize(int i, double cost, bool ForceDownhill);
	//takes one step for the exponent of the i'th' pole
	//returns the new_cost after the step: 
	//	new_cost < cost: the step was downhill
	//	new_cost >= cost: the step was non-downhill (ForceDownhill was false and the poles have changed)
	//	new_cost == -1.0f:  no downhill step could be taken (ForceDownhill was set true and the poles haven't changed)
	double ExponentMinimize(int i, double cost, bool ForceDownhill);
};

