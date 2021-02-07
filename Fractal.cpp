#include "Fractal.h"
#include <cmath>
#include <ctime>
#include <assert.h>

// Constructs the fractal and reads from desired.csv
Fractal::Fractal(int it, int bail, Dist dist, Box box) :
	iterations(it), bailout(bail), poles(), bounds(box), pixels(), desired(), rng(time(0)), dist(dist)
{
	dx = (float)(bounds.Width()) / (float)p;
	dy = (float)(bounds.Height()) / (float)p;

	//read from desired.csv and save the desired image
	std::ifstream des("desired.csv");
	std::string line;

	int t = 0;
	while (std::getline(des, line))
	{
		float v = std::stof(line);
		coordinates[t].x = bounds.x0 + t / (float)p * dx;
		coordinates[t].y = bounds.y0 + (t % p) * dy;
		desired[t] = v;
		t++;
	}
	des.close();

	//for (int i = 0; i < relevant; i++)
	//{
	//	std::cout << coordinates[i].x << " | " << coordinates[i].y << " : " << desired[i] << std::endl;
	//}
}

//
void Fractal::Randomize(int attempts)
{
	float cost;
	float min_cost = 1.0f;
	Pole min_params[N];
	for (int i = 0; i < attempts; i++)
	{
		for (int j = 0; j < N; j++)
		{
			poles[j].x = dist.Distx(rng);
			poles[j].y = dist.Disty(rng);
			poles[j].m = dist.Distm(rng);
		}
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
}

//Fractal function
inline float Fractal::Func(Complex q) const
{
	for (int i = 0; i < iterations; i++)
	{
		float Z = q.x * q.x + q.y * q.y;
		//float L = log(Z);

		if (Z > bailout)
		{
			return 1 - (float)i / (float)iterations;
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
	return 0.0f;
}

void Fractal::SubIterate(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		pixels[i] = Func(coordinates[i]);
	}
}

void Fractal::Iterate()
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
float convergent_weight = 3.0f;
float Fractal::Cost()
{
	float sum = 0.0f;
	for (int i = 0; i < pixels_size; i++)
	{
		float q = pixels[i], d = desired[i];
		float a = (q - d) * (q - d);
		//weight for convergent to be preferred
		if (q < d)
			a /= convergent_weight;
		sum += a;
	}
	sum = sqrt(sum / (float)pixels_size);
	return sum;
}

Complex Fractal::PosDerivative(int i, float cost)
{
	Complex copy = poles[i];
	Complex out;

	//get d/dx
	poles[i].x += pos_step;
	Iterate();
	out.x = (Cost() - cost) / pos_step;
	poles[i].x = copy.x;

	//get d/dy
	poles[i].y += pos_step;
	Iterate();
	out.y = (Cost() - cost) / pos_step;
	poles[i].y = copy.y;

	return out;
}

float Fractal::PowerDerivative(int i, float cost)
{
	float m = poles[i].m;
	float out = 0;

	poles[i].m += power_step;
	Iterate();
	out = (Cost() - cost) / power_step;
	poles[i].m = m;

	return out;
}

bool Fractal::PosCycle(int i, float cost, bool ForceDownhill)
{
	Pole copy = poles[i];

	Complex grad = -PosDerivative(i, cost);

	float new_cost, stepsize = 1;
	for (int j = 0; j < cost_steps; j++)
	{
		poles[i] = copy;
		poles[i] += grad * stepsize;
		Iterate();
		new_cost = Cost();
		if (new_cost < cost)
		{
			return true;
		}
		stepsize *= 0.1f;
	}
	if (ForceDownhill)
	{
		//reset if no downhill step was found
		poles[i] = copy;
	}
	else
	{
		//continue with the non-downhill step
		return true;
	}
	return false;
}

bool Fractal::PowerCycle(int i, float cost, bool ForceDownhill)
{
	float copy = poles[i].m;

	float grad = -PowerDerivative(i, cost);

	float new_cost, stepsize = 1;
	for (int j = 0; j < cost_steps; j++)
	{
		poles[i].m = copy;
		poles[i].m += grad * stepsize;
		Iterate();
		new_cost = Cost();
		if (new_cost < cost)
		{
			return true;
		}
		stepsize *= 0.1f;
	}
	if (ForceDownhill)
	{
		//reset if no downhill step was found
		poles[i].m = copy;
	}
	else
	{
		//continue with the non-downhill step
		return true;
	}
	return false;
}

void Fractal::Print()
{
	std::string s;
	for (int i = 0;; i++)
	{
		std::ifstream pot("pixels_" + std::to_string(i) + ".csv");
		if (!pot.good())
		{
			s = std::to_string(i) + ".csv";
			break;
		}
	}

	std::ofstream pix;
	pix.open("pixels_" + s);
	for (int i = 0; i < pixels_size; i++)
	{
		pix << pixels[i] << std::endl;
	}
	pix.close();

	std::ofstream par;
	par.open("parameters_" + s);
	par << "Cost: " << Cost() << std::endl;
	for (Pole m : poles)
	{
		par << m.string() << std::endl;
	}
	par.close();
}
