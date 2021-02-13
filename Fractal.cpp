#include "Fractal.h"
#include <cmath>
#include <ctime>
#include <assert.h>
#include <array>
#include <algorithm>
#include <numeric>

// Constructs the fractal and reads from desired.csv
Fractal::Fractal(int it, int bail, Dist dist, Box box) :
	iterations(it), bailout(bail), poles(), bounds(box), pixels(), desired(), rng(static_cast<unsigned int>(time(0))), dist(dist)
{
	dx = (double)(bounds.Width()) / (double)p;
	dy = (double)(bounds.Height()) / (double)p;

	//read from desired.csv and save the desired image
	std::ifstream des("desired.csv");
	std::string line;

	int t = 0;
	while (std::getline(des, line))
	{
		double v = std::stof(line);
		coordinates[t].x = bounds.x0 + t / (double)p * dx;
		coordinates[t].y = bounds.y0 + (t % p) * dy;
		desired[t] = v;
		t++;
	}
	des.close();
}

//
double Fractal::Randomize(int attempts)
{
	double cost;
	double min_cost = 1.0;
	Pole min_params[N];
	for (int i = 0; i < attempts; i++)
	{
		for (int j = 0; j < N; j++)
		{
			poles[j].x = dist.Distx(rng);
			poles[j].y = dist.Disty(rng);
			poles[j].m = dist.Distm(rng);
		}
		Iterate();
		cost = Cost();

		if (cost <= min_cost)
		{
			min_cost = cost;
			for (int j = 0; j < N; j++)
			{
				min_params[j] = poles[j];
			}
		}
	}

	//set minimum cost parameters
	for (int j = 0; j < N; j++)
		poles[j] = min_params[j];

	return min_cost;
}

//Fractal function
inline double Fractal::Func(Complex q) const
{
	for (int i = 0; i < iterations; i++)
	{
		if (q.AbsSquared() > bailout)
		{
			return (iterations - i) / (float)iterations;
		}

		Complex R(1, 0);
		/** f(z) **/
		for (int j = 0; j < N; j++)
		{
			R *= poles[j].poly(q);
		}
		R *= Complex(exp(C), 0);
		/****/

		q = R;
	}
	return 0.0;
}

inline void Fractal::SubIterate(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		pixels[i] = Func(coordinates[i]);
	}
}

inline void Fractal::Iterate()
{
	//assign threads to their piece
	for (int i = 0; i < thread_count - 1; i++)
	{
		threads[i] = std::thread(&Fractal::SubIterate, this, ppt * i, ppt * (i + 1));
	}
	//final thread is a little bigger
	threads[thread_count - 1] = std::thread(&Fractal::SubIterate, this, ppt * (thread_count - 1), pixels_size);

	//wait for threads
	for (int i = 0; i < thread_count; i++)
	{
		threads[i].join();
	}
}

//weight used in this specific energy function
constexpr double convergent_weight = 3.0;
double Fractal::Cost()
{
	double sum = 0.0;
	for (int i = 0; i < pixels_size; i++)
	{
		double q = pixels[i], d = desired[i];
		double a = (q - d) * (q - d);
		//weight for convergent to be preferred
		if (q < d)
			a /= convergent_weight;
		sum += a;
	}
	sum = sqrt(sum / (double)pixels_size);
	return sum;
}

#if GRADIENT_DESCENT
const double pos_h = 0.1;

Vector Fractal::PosDerivative(int i, double cost)
{
	Complex copy = poles[i];
	Vector out;
	double cost1, cost2;

	//first term
	poles[i].x += pos_h;
	Iterate();
	cost1 = Cost();
	poles[i].x = copy.x;
	//second term
	poles[i].x -= pos_h;
	Iterate();
	cost2 = Cost();
	poles[i].x = copy.x;
	//d/dx
	if (cost <= cost1 && cost <= cost2)
		//valley
		out.x = 0;
	else
		out.x = (cost2 - cost1) / double(2.0 * pos_h);

	//first term
	poles[i].y += pos_h;
	Iterate();
	cost1 = Cost();
	poles[i].y = copy.y;
	//second term
	poles[i].y -= pos_h;
	Iterate();
	cost2 = Cost();
	poles[i].y = copy.y;
	//d/dy
	if (cost <= cost1 && cost <= cost2)
		//valley
		out.y = 0;
	else
		out.y = (cost2 - cost1) / double(2.0 * pos_h);

	return out;
}

#if INTEGER_EXPONENT
const int power_h = 1;
#else
const double power_h = 0.1;
#endif
double Fractal::ExponentDerivative(int i, double cost)
{
	EXPONENT_TYPE m = poles[i].m;
	double out = 0;
	double cost1, cost2;

	//first term
	poles[i].m += power_h;
	Iterate();
	cost1 = Cost();
	poles[i].m = m;
	//second term
	poles[i].m -= power_h;
	Iterate();
	cost2 = Cost();
	poles[i].m = m;
	//d/dm
	if (cost <= cost1 && cost <= cost2)
		//valley
		out = 0;
	else
		out = (cost2 - cost1) / double(2 * power_h);

	return out;
}

#else
//simplex algorithm
double Fractal::PosMinimize(int i, double cost, bool ForceDownhill)
{
	//3 Dimensional parameter => 4 poles

	// initial pole
	double x = 0, y = 0, m = 0;
	double dx = 0.3, dy = 0.3, dm = 0.1;
	//other poles
	std::array<Pole, 4> polytope;
	polytope[0] = Pole(x, y, m);
	polytope[1] = Pole(x + dx, y, m);
	polytope[2] = Pole(x, y + dy, m);
	polytope[3] = Pole(x, y, m + dm);
	//sort poles


	Pole centroid(0, 0, 0);
	for (int i = 0; i < 3; i++)
	{
		centroid.y += polytope[i].y;
		centroid.m += polytope[i].m;
		centroid.x += polytope[i].x;
	}
	centroid.x / 3.0;
	centroid.y / 3.0;
	centroid.m / 3.0;

	return 0;
}
#endif

void Fractal::Print()
{
	std::string s;
	for (int i = 0;; i++)
	{
		std::ifstream pot("data/pixels_" + std::to_string(i) + ".csv");
		if (!pot.good())
		{
			s = std::to_string(i) + ".csv";
			break;
		}
	}

	std::ofstream pix;
	pix.open("data/pixels_" + s);
	for (int i = 0; i < pixels_size; i++)
	{
		pix << pixels[i] << std::endl;
	}
	pix.close();

	std::ofstream par;
	par.open("data/parameters_" + s);
	par << "Cost: " << Cost() << std::endl;
	for (Pole p : poles)
	{
		par << p.string() << std::endl;
	}
	par.close();
}
