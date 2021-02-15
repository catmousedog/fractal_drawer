
#include <cstdlib>
#include "Trainer.h"

void Trainer::TrainPosOne(int i)
{
	std::cout << "TrainPosOne " << i << std::endl;
	double cost = Randomize(10);

	std::cout << "Randomize: " << cost << std::endl;

	double new_cost = -1.0;
	for (int j = 0;; j++)
	{
		new_cost = PosMinimize(i, cost, ForceDownhill, Vector(0, 0));
		// could not find downhill step
		if (new_cost < 0)
		{
			std::cout << "could not take downhill step" << std::endl;
			break;
		}
		// downhill step
		else if (new_cost < cost)
		{
			cost = new_cost;
			std::cout << j << "\t downhill: " << new_cost << std::endl;
		}
		// non-downhill step
		else
		{
			cost = new_cost;
			std::cout << j << "\t uphill: " << new_cost << std::endl;
		}
	}
	//check if previous cost can be printed as new_cost is -1.0
	if (cost < MinCost)
	{
		std::cout << "printing" << std::endl;
		Print();
	}
}

void Trainer::TrainPosAll() {}

void Trainer::TrainPowerOne() {}

void Trainer::TrainPowerAll() {}

void Trainer::TrainAllOne() {}

void Trainer::TrainAllAll() {}

Trainer::StepData<Vector> Trainer::PosMinimize(int i, double cost, bool ForceDownhill, Vector PrevStep)
{
	Pole copy = poles[i];
	Vector grad = -PosDerivative(i, cost);

	if (grad.IsZero())
	{
		std::cout << "minimum reached" << std::endl;
		ConditionalPrint(cost);
		return StepData<Vector>(-1.0, Vector());
	}

	double new_cost = -2.0;
	Vector s = sgn(PrevStep);
	Vector stepsize = PrevStep + s.TermMultiply(pos_eps_vec);

	do {
		poles[i] += s.TermMultiply(stepsize);
		Iterate();
		new_cost = Cost();
		if (new_cost < cost)
		{
			return StepData<Vector>(new_cost, stepsize);
		}

		stepsize -= pos_eps_vec;
	} while (abs(stepsize.x) >= pos_eps && abs(stepsize.y) >= pos_eps);

	std::cout << "NOT DOWNHILL" << std::endl;
	//not downhill
	if (ForceDownhill)
	{
		//don't take step
		poles[i] = copy;
		return -1.0;
	}
	else
	{
		//continue with the non-downhill step
		return new_cost;
	}
}

Trainer::StepData<double> Trainer::ExponentMinimize(int i, double cost, bool ForceDownhill, double PrevStep)
{
	EXPONENT_TYPE copy = poles[i].m;
	double grad = -ExponentDerivative(i, cost);

	if (grad == 0.0)
	{
		std::cout << "minimum reached" << std::endl;
		ConditionalPrint(cost);
		return StepData<double>(-1.0, 0.0);
	}

	double new_cost = -2.0;
	double s = sgn(PrevStep);
	double stepsize = PrevStep + s * exponent_eps;

	do {
		poles[i].m += s * stepsize;
		Iterate();
		new_cost = Cost();
		if (new_cost < cost)
		{
			return StepData<double>(new_cost, stepsize);
		}

		stepsize -= exponent_eps;
	} while (stepsize >= exponent_eps);

	std::cout << "NOT DOWNHILL" << std::endl;
	//not downhill
	if (ForceDownhill)
	{
		//don't take step
		poles[i].m = copy;
		std::cout << "no downhill step found" << std::endl;
		ConditionalPrint(cost);
		return StepData<double>(-1.0, 0.0);
	}
	else
	{
		//continue with the non-downhill step
		return StepData<double>(new_cost, stepsize);;
	}
}

