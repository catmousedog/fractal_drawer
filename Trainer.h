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
	//does one training cycle for the position of the i'th' pole
	//returns the new_cost after the cycle: 
	//	new_cost < cost: the step was downhill
	//	new_cost >= cost: the step was not downhill and ForceDownhill was false (poles have changed)
	//	new_cost == -1.0f:  the step was not downhill and ForceDownhill was set true (poles haven't changed)
	double PosMinimize(int i, double cost, bool ForceDownhill);
	//does one training cycle for the exponent of the i'th' pole
	//returns true if the step was downhill (New_Cost < Prev_Cost)
	//if ForceDownhill is set to true it will always take a step so that: New_Cost <= Prev_Cost
	double ExponentMinimize(int i, double cost, bool ForceDownhill);
};

