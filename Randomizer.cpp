#pragma once

#include "Randomizer.h"

double Randomizer::operator()(int R)
{
	Pole minPoles[Fractal2::N];
	//first cycle
	RandomizeE();
	RandomizeP();
	for (int i = 0; i < Fractal2::N; i++)
		minPoles[i] = f.poles[i];
	f.Iterate();
	double Emin = op.Energy();
	std::cout << R << ": " << Emin << std::endl;

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
			for (int i = 0; i < Fractal2::N; i++)
				minPoles[i] = f.poles[i];

			Emin = E;
		}
	}
	for (int i = 0; i < Fractal2::N; i++)
		f.poles[i] = minPoles[i];
	
	f.Iterate(); //make sure pixels are correct
	return Emin;
}


double Randomizer::RandomizeE(int R)
{
	Pole* minPoles = f.poles;
	//first cycle
	RandomizeE();
	for (int i = 0; i < Fractal2::N; i++)
		minPoles[i] = f.poles[i];
	f.Iterate();
	double Emin = op.Energy();
	std::cout << R << ": " << Emin << std::endl;

	//other cycles
	for (int j = 0; j < R - 1; j++)
	{
		RandomizeE();
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
		f.poles[i] = minPoles[i];

	return Emin;
}

double Randomizer::RandomizeP(int R)
{
	Pole* minPoles = f.poles;
	//first cycle
	RandomizeP();
	for (int i = 0; i < Fractal2::N; i++)
		minPoles[i] = f.poles[i];
	f.Iterate();
	double Emin = op.Energy();
	std::cout << R << ": " << Emin << std::endl;

	//other cycles
	for (int j = 0; j < R - 1; j++)
	{
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
		f.poles[i] = minPoles[i];

	return Emin;
}

void Randomizer::RandomizeE()
{
	for (int i = 0; i < Fractal2::N; i++)
	{
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