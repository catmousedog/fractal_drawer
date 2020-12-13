#include "Fractal.h"
#include <cmath>
#include <ctime>
#include <assert.h>

Fractal::Fractal(int it, int bail, float m, float M, Box box) :
	iterations(it), bailout(bail), parameters(), bounds(box), pixels(), desired(), rng(time(0)), dist(m, M)
{
	dx = (float)(bounds.x1 - bounds.x0) / (float)p;
	dy = (float)(bounds.y1 - bounds.y0) / (float)p;

	std::ifstream des("desired.csv");
	std::string line;

	//first line is amount of relevant pixels (not -1)
	std::getline(des, line);
	relevant = std::stof(line);

	std::cout << "relevant pixels: " << relevant << std::endl;

	coordinates = new Complex[relevant];
	desired = new float[relevant];
	pixels = new float[relevant];

	//total / relevant counter
	int t = 0, r = 0;
	while (std::getline(des, line))
	{
		float v = std::stof(line);
		if (v >= 0)
		{
			assert(r < relevant);
			coordinates[r].x = bounds.x0 + t / (float)p * dx;
			coordinates[r].y = bounds.y0 + (t % p) * dy;
			desired[r] = v;
			r++;
		}
		t++;
	}
	des.close();

	//for (int i = 0; i < relevant; i++)
	//{
	//	std::cout << coordinates[i].x << " | " << coordinates[i].y << " : " << desired[i] << std::endl;
	//}
}

void Fractal::Randomize(int attempts, int limit)
{
	float cost;
	float min_cost = 1.0f;
	Complex min_params[m];
	std::cout << "randomize: ";
	for (int i = 0; i < attempts; i++)
	{
		std::cout << i << ", ";
		for (int j = 0; j < limit; j++)
		{
			parameters[j].x = dist(rng);
			parameters[j].y = dist(rng);
		}
		cost = Cost();

		if (cost < min_cost)
		{
			min_cost = cost;
			for (int j = 0; j < limit; j++)
			{
				min_params[j] = parameters[j];
			}
		}
	}

	std::cout << std::endl;

	//set minimum cost parameters
	for (int j = 0; j < m; j++)
		parameters[j] = min_params[j];
}

inline float Fractal::Func(float cx, float cy) const
{
	float x = cx, y = cy;
	for (int i = 0; i < iterations; i++)
	{
		float s = x * x + y * y;

		if (s > bailout)
		{
			return 1 - (float)i / (float)iterations;
		}

		float tx = x, ty = y;
		/** f(z) **/

		for (int n = 0; n < m; n++)
		{
			//z^n
			//float a = pow(s, (float)n / 2.0f);
			//float t = (float)n * atan2(y, x);
			//tx += parameters[n].x * a * cos(t) + cx;
			//ty += parameters[n].y * a * sin(t) + cy;

			//almost e^iz
			//float a = exp(-parameters[n].x * y);
			//float t = parameters[n].x * x;
			//tx += parameters[n].y * a * cos(t) + cx;
			//ty += parameters[n].y * a * sin(t) + cy;

			//e^iz C included
			float a = exp(-parameters[n].y * y);
			float t = parameters[n].y * x;
			tx += parameters[n].x * (a * cos(t) + cx);
			ty += parameters[n].x * (a * sin(t) + cy);
		}

		/****/
		x = tx;
		y = ty;
	}
	return 0.0f;
}

void Fractal::SubIterate(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		Complex c = coordinates[i];
		pixels[i] = Func(c.x, c.y);
	}
}

void Fractal::Iterate()
{
	int dp = relevant / thread_count;

	//assign threads to their piece
	for (int i = 0; i < thread_count - 1; i++)
	{
		threads[i] = std::thread(&Fractal::SubIterate, this, dp * i, dp * (i + 1));
	}
	//final thread is a little bigger
	threads[thread_count - 1] = std::thread(&Fractal::SubIterate, this, dp * (thread_count - 1), relevant);

	//wait for threads
	for (int i = 0; i < thread_count; i++)
	{
		threads[i].join();
	}
}

float Fractal::Cost()
{
	Iterate();
	float sum = 0.0f;
	for (int i = 0; i < relevant; i++)
	{
		float p = pixels[i], d = desired[i];
		float a = (p - d) * (p - d);
		//weight for convergent to be preferred
		if (p < d)
			a /= convergent_weight;
		sum += a;
	}
	sum = sqrt(sum / (float)relevant);
	return sum;
}

Fractal::Complex Fractal::Derivative(int i, float cost)
{
	Complex p = parameters[i];
	Complex out;

	//get d/dx
	parameters[i].x += dstep;
	out.x = (Cost() - cost) / dstep;
	parameters[i].x = p.x;

	//get d/dy
	parameters[i].y += dstep;
	out.y = (Cost() - cost) / dstep;
	parameters[i].y = p.y;

	return out;
}

bool Fractal::Cycle(bool ForceDownhill)
{
	auto start = std::chrono::steady_clock::now();

	//make copy of parameters
	Complex params[m];
	for (int i = 0; i < m; i++)
		params[i] = parameters[i];

	float cost = Cost();
	//calculate negative gradient
	Complex grad[m];
	for (int i = 0; i < m; i++)
	{
		grad[i] = -Derivative(i, cost);
	}

	//check if step is downhill
	int j = 0;
	float power = 1.0f;
	float cost_end;
	do {

		//apply gradient
		for (int i = 0; i < m; i++)
			parameters[i] = params[i] + grad[i] * power;

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
				for (int i = 0; i < m; i++)
				{
					parameters[i] = params[i];
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
	for (int r = 0; r < relevant; r++)
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
	for (Complex m : parameters)
	{
		par << m.string() << std::endl;
	}
	par << Cost();
	par.close();
}