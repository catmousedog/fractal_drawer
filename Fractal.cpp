#include "Fractal.h"
#include <cmath>
#include <ctime>
#include <assert.h>

// Constructs the fractal and reads from desired.csv
Fractal::Fractal(int it, int bail, float m, float M, Box box) :
	iterations(it), bailout(bail), poles(), bounds(box), pixels(), desired(), rng(time(0)), dist(m, M)
{
	dx = (float)(bounds.x1 - bounds.x0) / (float)p;
	dy = (float)(bounds.y1 - bounds.y0) / (float)p;

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
//void Fractal::Randomize(int attempts, int limit)
//{
//	float cost;
//	float min_cost = 1.0f;
//	Pole min_params[N];
//	std::cout << "randomize: ";
//	for (int i = 0; i < attempts; i++)
//	{
//		std::cout << i << ", ";
//		for (int j = 0; j < limit; j++)
//		{
//			poles[j].x = dist(rng);
//			poles[j].y = dist(rng);
//		}
//		cost = Cost();
//
//		if (cost < min_cost)
//		{
//			min_cost = cost;
//			for (int j = 0; j < limit; j++)
//			{
//				min_params[j] = poles[j];
//			}
//		}
//	}
//
//	std::cout << std::endl;
//
//	//set minimum cost parameters
//	for (int j = 0; j < N; j++)
//		poles[j] = min_params[j];
//}

//Fractal function
inline float Fractal::Func(Complex c) const
{
	//use the more optimized pole
	Pole q(c.x, c.y, 0);
	for (int i = 0; i < iterations; i++)
	{
		float Z = q.x * q.x + q.y * q.y;
		//float L = log(Z);

		if (Z > bailout)
		{
			return 1 - (float)i / (float)iterations;
		}

		//float tx = x, ty = y;
		/** f(z) **/
		Complex R(1, 0);

		for (int j = 0; j < N; j++)
		{

			poles[j].poly(q);

			//float P = poles[j].m;
			//Complex z = (q - poles[j]);
			//float A = exp(P * L / 2);
			//float theta = atan2(z.y, z.x);
			//z.x = A * cos(theta * P);
			//z.y = A * sin(theta * P);

			//R *= z;
		}

		R *= exp(C);
		R += Complex(1, 2);
		q = R;

		/****/
		//x = tx;
		//y = ty;
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
/**
float Fractal::Cost()
{
	Iterate();
	float sum = 0.0f;
	for (int i = 0; i < pixels_size; i++)
	{
		float p = pixels[i], d = desired[i];
		float a = (p - d) * (p - d);
		//weight for convergent to be preferred
		if (p < d)
			a /= convergent_weight;
		sum += a;
	}
	sum = sqrt(sum / (float)pixels_size);
	return sum;
}

Complex Fractal::Derivative(int i, float cost)
{
	Complex p = poles[i];
	Complex out;

	//get d/dx
	poles[i].x += dstep;
	out.x = (Cost() - cost) / dstep;
	poles[i].x = p.x;

	//get d/dy
	poles[i].y += dstep;
	out.y = (Cost() - cost) / dstep;
	poles[i].y = p.y;

	return out;
}

bool Fractal::Cycle(bool ForceDownhill)
{
	auto start = std::chrono::steady_clock::now();

	//make copy of parameters
	Pole params[N];
	for (int i = 0; i < N; i++)
		params[i] = poles[i];

	float cost = Cost();
	//calculate negative gradient
	Pole grad[N];
	for (int i = 0; i < N; i++)
	{
		grad[i] = -Derivative(i, cost);
	}

	//check if step is downhill
	int j = 0;
	float power = 1.0f;
	float cost_end;
	do {

		//apply gradient
		for (int i = 0; i < N; i++)
			poles[i] = params[i] + grad[i] * power;

		cost_end = Cost();

		if (cost_end < cost)
			break;

		power /= 2;
		j++;

		//max steps exceeded
		if (j > csteps)
		{
			auto end = std::chrono::steady_clock::now();
			std::cout << cost_end << " | exec: "
				<< (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count()
				<< "ms | could not go downhill!\n";

			//for (int i = 0; i < m; i++)
			//{
			//	std::cout << grad[i].x << ", ";,
			//}
			//std::cout << std::endl;

			// if forced downhill
			if (ForceDownhill)
			{
				//reset parameters to lowest
				for (int i = 0; i < N; i++)
				{
					poles[i] = params[i];
				}
				//stop cycling
				return false;
			}
			else
			{
				//continue cycling
				return true;
			}
		}
	} while (true);

	auto end = std::chrono::steady_clock::now();
	std::cout << cost_end << " | exec: "
		<< (std::chrono::duration_cast<std::chrono::milliseconds>(end - start)).count()
		<< "ms\n";
	return true;
}

inline bool Fractal::InCoordinates(float x, float y)
{
	for (int r = 0; r < pixels_size; r++)
	{
		if (coordinates[r].x == x && coordinates[r].y == y)
		{
			return true;
		}
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
	int r = 0;
	for (int t = 0; t < pixels_size; t++)
	{
		float x = bounds.x0 + t / (float)p * dx;
		float y = bounds.y0 + (t % p) * dy;
		if (InCoordinates(x, y))
		{
			pix << pixels[r] << std::endl;
			r++;
		}
		else
		{
			pix << -1.0f << std::endl;
		}
	}
	pix.close();

	std::ofstream par;
	par.open("parameters_" + s);
	for (Pole m : poles)
	{
		par << m.string() << std::endl;
	}
	par << Cost();
	par.close();
}
**/