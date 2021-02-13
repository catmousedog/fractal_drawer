
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
		new_cost = PosMinimize(i, cost, ForceDownhill);
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

double Trainer::PosMinimize(int i, double cost, bool ForceDownhill)
{
	Pole copy = poles[i];
	Vector grad = -PosDerivative(i, cost);

	if (grad.IsZero())
	{
		std::cout << "gradient is zero" << std::endl;
		return -1.0;
	}

	//backtracking line search
	double stepsize = 1, c = 0.5, reduction = 0.5;
	double new_cost;
	while (true)
	{
		poles[i] = copy + grad * stepsize;
		Iterate();
		new_cost = Cost();

		if (new_cost - cost > -c * stepsize * sqrt(grad.AbsSquared()))
			break;

		stepsize *= reduction;
	}

	std::cout << "backtrack " << grad.string() << " " << stepsize << std::endl;

	//downhill
	if (new_cost < cost)
	{
		return new_cost;
	}
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

double Trainer::ExponentMinimize(int i, double cost, bool ForceDownhill)
{
	EXPONENT_TYPE copy = poles[i].m;
	double grad = -ExponentDerivative(i, cost);

	if (grad == 0.0)
	{
		std::cout << "minimum reached" << std::endl;
		return -1.0;
	}

	//backtracking line search
	double stepsize = 1.0; //whole number
	double c = 0.5, reduction = 0.5;
	double new_cost;
	while (true)
	{
#if INTEGER_EXPONENT
		poles[i].m = copy + sgn(grad);
		Iterate();
		new_cost = Cost();
		break;
#endif
		poles[i].m = copy + grad * stepsize;

		Iterate();
		new_cost = Cost();

		if (new_cost - cost > -c * stepsize * grad)
			break;

		stepsize *= reduction;
	}

	std::cout << "backtrack " << grad << " " << stepsize << std::endl;

	//downhill
	if (new_cost < cost)
	{
		return new_cost;
	}
	//not downhill
	if (ForceDownhill)
	{
		//don't take step
		poles[i].m = copy;
		return -1.0;
	}
	else
	{
		//continue with the non-downhill step
		return new_cost;
	}
}