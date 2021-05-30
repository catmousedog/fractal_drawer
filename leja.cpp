#include "leja.h"

Leja::Leja(int N, double (*X)(double), double (*Y)(double))
{
	////read from image
	//std::ifstream des("boundary.csv");
	//std::string line;

	////counter
	//int t = 1;
	//while (std::getline(des, line))
	//{
	//	deq d = split(line, ', ');
	//	double x = std::stod(d.at(0));
	//	double y = std::stod(d.at(1));
	//	boundary.push_back(Complex(x, y));

	//	t++;
	//}
	//des.close();

	for (int i = 0; i < N; i++)
	{
		double t = i / (double)N;
		boundary.push_back(Complex(X(t), Y(t)));
	}

	points.push_back(boundary.front());
}

void Leja::add(int N)
{
	for (int i = 0; i < N; i++)
	{
		double max = -1;
		Complex out(0, 0);
		for (Complex c : boundary)
		{
			double m = func(c);
			if (m > max)
			{
				max = m;
				out = c;
			}
		}
		points.push_back(out);
	}
	setConstant();
}

void Leja::setConstant()
{
	C = exp(-(signed int)points.size() * s / 2.0);
	double prod = 1;
	Complex last = points.back();
	for (int i = 0; i < points.size() - 1; i++)
	{
		prod *= sqrt((last - points.at(i)).AbsSquared());
	}
	C /= prod;
}

double Leja::func(Complex z)
{
	double prod = 1.0;
	for (Complex c : points)
	{
		prod *= sqrt((z - c).AbsSquared());
	}
	return prod;
}