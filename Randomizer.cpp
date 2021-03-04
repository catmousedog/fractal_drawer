#pragma once

#include "Randomizer.h"

double Randomizer::operator()(int R)
{
	//first cycle
	RandomizeE();
	RandomizeP();
	f.Iterate();
	Pole* minPoles = f.poles;
	double Emin = op.Energy();

	//other cycles
	for (int j = 0; j < R - 1; j++)
	{
		RandomizeE();
		RandomizeP();
		f.Iterate();
		double E = op.Energy();
		if (E < Emin)
		{
			std::cout << R - 1 - j << ": " << E << std::endl;
			minPoles = f.poles;
			Emin = E;
		}
	}
	for (int i = 0; i < Fractal2::N; i++)
	{
		f.poles[i] = minPoles[i];
	}
	return Emin;
}

void Randomizer::RandomizeE()
{
	for (int i = 0; i < Fractal2::N; i++)
	{
		if (dist.Mm > 0)
			f.poles[i].m = dist.Distm(rng);
	}
}

void Randomizer::RandomizeP()
{
	for (int i = 0; i < Fractal2::N; i++)
	{
		f.poles[i].x = dist.Distx(rng);
		f.poles[i].y = dist.Disty(rng);
	}
}