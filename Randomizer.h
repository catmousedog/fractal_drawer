#pragma once

#include "Optimizer.h"
#include <random>
#include <ctime>

class Randomizer
{

private:

	std::mt19937 rng;

public:

	Fractal2& f;
	Optimizer& op;

	Randomizer(Fractal2& f, Optimizer& op, int mm, int Mm) : f(f), op(op), dist(f, mm, Mm), rng((unsigned int)time(0))
	{
	}


	struct Dist
	{
		double mx, Mx;
		std::uniform_real_distribution<double> Distx;
		double my, My;
		std::uniform_real_distribution<double> Disty;
		int mm, Mm;
		std::uniform_int_distribution<int> Distm;

		Dist(Fractal2& f, int mm, int Mm) : Distx(f.bounds.x0, f.bounds.x1), Disty(f.bounds.y0, f.bounds.y1), Distm(mm, Mm)
		{
			this->mx = f.bounds.x0;
			this->Mx = f.bounds.x1;
			this->my = f.bounds.y0;
			this->My = f.bounds.y1;
			this->mm = mm;
			this->Mm = Mm;
		}
		Dist(double mx, double Mx, double my, double My, int mm, int Mm) : Distx(mx, Mx), Disty(my, My), Distm(mm, Mm)
		{
			this->mx = mx;
			this->Mx = Mx;
			this->my = my;
			this->My = My;
			this->mm = mm;
			this->Mm = Mm;
		}
		Dist(const Dist& dist) : Distx(dist.mx, dist.Mx), Disty(dist.my, dist.My), Distm(mm, Mm)
		{
			mx = dist.mx;
			Mx = dist.Mx;
			my = dist.my;
			My = dist.My;
			mm = dist.mm;
			Mm = dist.Mm;
		}
	} dist;

	//randomizes all in 'i' attempts and returns the best energy
	double operator()(int R);

	//randomize exponents
	double RandomizeE(int R);

	//randomize pos
	double RandomizeP(int R);

	//randomize exponents
	void RandomizeE();

	//randomize pos
	void RandomizeP();


};

