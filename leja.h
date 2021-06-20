#pragma once

#include <vector>
#include <fstream>
#include "Complex.h"

class Leja
{
public:

	int N = 1;

	class Region
	{
	public:

		std::vector<Complex> boundary;
		std::vector<Complex> leja;
		double s = 1;

		Region(std::vector<Complex>& boundary) : boundary(boundary)
		{
			leja.push_back(boundary.front());
		}

		Region(int N, double (*X)(double), double (*Y)(double))
		{
			for (int i = 0; i < N; i++)
			{
				double t = i / (double)N;
				boundary.push_back(Complex(X(t), Y(t)));
			}
			leja.push_back(boundary.front());
		}

		void Add(int N)
		{
			for (int i = 0; i < N; i++)
			{
				double max = -1;
				Complex out;
				for (Complex& b : boundary)
				{
					double m = LejaDistance(b);
					if (m > max)
					{
						max = m;
						out = b;
					}
				}
				leja.push_back(out);
			}
			setConstant(s);
		}

		void setConstant(double s)
		{
			this->s = s;
			C = exp(-(signed int)leja.size() * s / 2.0);
			double prod = 1;
			Complex last = leja.back();
			for (int i = 0; i < leja.size() - 1; i++)
			{
				prod *= sqrt((last - leja.at(i)).AbsSquared());
			}
			C /= prod;
		}

		Complex Omega(const Complex z)
		{
			Complex R(1, 0);
			for (Complex& p : leja)
			{
				R *= z - p;
			}
			R *= C;
			return R;
		}

	private:

		double C = 1;

		double LejaDistance(Complex z)
		{
			double prod = 1.0;
			for (Complex c : leja)
			{
				prod *= sqrt((z - c).AbsSquared());
			}
			return prod;
		}
	};

	std::vector<Region> regions;

	Leja();

	void Add(int N);

};

