#pragma once

#include "main.h"

double a = 2;
Fractal2::Box bounds(-a, -a, a, a);
Fractal2 fractal(20, 10000, bounds);
Optimizer optimizer(fractal);
Drawer drawer(fractal);
Randomizer random(fractal, optimizer, -2, 8);

str Step(deq arg)
{
	if (arg.size() == 2)
	{
		try
		{
			int min = std::stod(arg.at(0));
			int mom = std::stoi(arg.at(1));
			optimizer.SetSteps(min, mom);
		}
		catch (const std::exception&)
		{
		}
	}
	else if (arg.size() == 3)
	{
		try
		{
			double x = std::stod(arg.at(0));
			double y = std::stod(arg.at(1));
			int m = std::stoi(arg.at(2));
			optimizer.SetStepSize(x, y, m);
		}
		catch (const std::exception&)
		{
		}
	}
	return "steps: " + std::to_string(optimizer.GetMinSteps()) + "|" +
		std::to_string(optimizer.GetMomentumSteps()) +
		"\nstepsize: " + std::to_string(optimizer.GetStepX()) + "|" +
		std::to_string(optimizer.GetStepY()) + "|" +
		std::to_string(optimizer.GetStepM());
}

str Random(deq arg)
{
	if (arg.size() > 0)
	{
		try
		{
			int a = std::stoi(arg.front());
			random(a);
		}
		catch (const std::exception&)
		{
		}
	}
	else
	{
		random(1);
	}
	return "done";
}

str Iterate(deq arg)
{
	fractal.Iterate();
	return "done";
}

str Descend(deq arg)
{
	bool changed = false;
	if (arg.size() > 0)
	{
		try
		{
			int i = std::stoi(arg.front());
			changed = Descend(i);
		}
		catch (const std::exception&)
		{
		}
	}
	else
	{
		changed = Descend();
	}
	if (changed)
		return "changed";
	return "unchanged";
}

str DescendM(deq arg)
{
	bool changed = false;
	if (arg.size() > 2)
	{
		try
		{
			int M = std::stoi(arg.at(0));
			changed = DescendM(M);
		}
		catch (const std::exception&)
		{
		}
	}
	if (changed)
		return "changed";
	return "unchanged";
}

str Train(deq arg)
{
	if (arg.size() > 2)
	{
		try
		{
			int A = std::stoi(arg.front());
			int R = std::stoi(arg.at(1));
			int M = std::stoi(arg.at(2));
			Train(A, R, M);
		}
		catch (const std::exception&)
		{
		}
	}
	return "done";
}

str Print(deq arg)
{
	double E = optimizer.NormEnergy();
	if (arg.size() > 0 && arg.front() == "file")
	{
		fractal.Print(E);
		return "printed to file";
	}
	fractal.out(E);
	return "printed to console";
}

str Draw(deq arg)
{
	drawer.Draw();
	return "";
}

int main()
{
	//pre console start
	random(100);
	optimizer.SetStepSize(0.2, 0.2, 1);
	DescendM(10);
	//std::cout << "fast exponent" << std::endl;
	//optimizer.SetSteps(2, 0);
	//optimizer.SetStepSize(0, 0, 2);
	//DescendM(5);
	//std::cout << "exponent end" << std::endl;
	//optimizer.SetSteps(2, 2);
	//optimizer.SetStepSize(0, 0, 1);
	//DescendM(2);
	//std::cout << "fast position" << std::endl;
	//optimizer.SetSteps(3, 0);
	//optimizer.SetStepSize(0.25, 0.25, 0);
	//DescendM(4);
	//std::cout << "position end" << std::endl;
	//optimizer.SetSteps(2, 2);
	//optimizer.SetStepSize(0.1, 0.1, 0);
	//DescendM(3);
	//std::cout << "all end" << std::endl;
	//optimizer.SetSteps(2, 2);
	//optimizer.SetStepSize(0.1, 0.1, 1);
	//DescendM(2);

	fractal.out(optimizer.NormEnergy());
	drawer.Draw();

	//console start
	std::map<str, fp> commands;
	commands["step"] = Step;
	commands["random"] = Random;
	commands["iterate"] = Iterate;
	commands["descend"] = Descend;
	commands["train"] = Train;
	commands["print"] = Print;
	commands["draw"] = Draw;

	std::cout << "--CONSOLE--\n";
	while (true)
	{
		str in;
		std::getline(std::cin, in);
		deq words = split(in, ' ');
		if (words.size() > 0)
		{
			std::map<str, fp>::iterator iter = commands.find(words.front());
			if (iter != commands.end())
			{
				fp f = iter->second;
				words.pop_front();
				std::cout << f(words) << std::endl;
			}
		}
	}

	return 0;
}

void Train(int A, int R, int M)
{
	for (int a = 0; a < A; a++)
	{
		std::cout << a << std::endl;
		random(R);
		DescendM(M);
		Print(optimizer.NormEnergy());
	}
}

bool DescendM(int M)
{
	for (int i = 0; i < M; i++)
	{
		std::cout << M - i << std::endl;
		if (!Descend())
			return false;
	}
	return true;
}

bool Descend()
{
	bool changed = false;
	for (int i = 0; i < Fractal2::N; i++)
	{
		if (Descend(i))
			changed = true;
	}
	return changed;
}

bool Descend(int i)
{
	bool changed = false;
	////x
	//double& x = fractal.GetPoles()[i].x;
	//double gradx = optimizer.GradientX(i);
	//if (gradx != 0)
	//{
	//	changed = true;
	//	x += gradx;
	//}
	////y
	//double& y = fractal.GetPoles()[i].y;
	//double grady = optimizer.GradientY(i);
	//if (grady != 0)
	//{
	//	changed = true;
	//	y += grady;
	//}
	//exponent
	int& m = fractal.GetPoles()[i].m;
	int gradm = optimizer.GradientE(i);
	if (gradm != 0)
	{
		changed = true;
		m += gradm;
	}
	//iterate
	fractal.Iterate();
	double gradx = 0, grady = 0;
	std::cout << i << ": " << optimizer.NormEnergy() << " += (" << gradx << ", " << grady << ", " << gradm << ")\n";

	return changed;
}

void Print(double E)
{
	if (E < Emin)
	{
		fractal.Print(E);
		drawer.Draw();
	}
}

//ENERGY TEST
	//for (int i = 0; i < Fractal2::pixels_size; i++)
	//{
	//	double x = f.GetCoordinates()[i].x;
	//	double y = f.GetCoordinates()[i].y;
	//	if (x * x + y * y < 1)
	//		f.GetPixels()[i] = 1;
	//	else
	//		f.GetPixels()[i] = 0;
	//	
	//}
	//std::cout << op.NormEnergy() << std::endl;
	//return 0;

	//r(10);
	//f.out();
	//f.Iterate();
	//std::cout << op.NormEnergy() << std::endl;
	//d.Draw();

	//GRAPH
	//int& m = f.GetPoles()[2].m;
	//int M = 2;
	//int b = m - M;
	//m = b;
	//std::vector<double> x, y;
	//double E;
	//for (int i = 0; i < 2 * M + 1; i++)
	//{
	//	f.Iterate();
	//	E = op.NormEnergy();

	//	x.push_back((m - b) / double(2 * M));
	//	y.push_back(E);
	//	std::cout << x.at(i) << ", " << y.at(i) << std::endl;
	//	m++;
	//}
	//d.Graph(x, y, b, m, 0, 1);
	//return 0;

void Benchmark()
{
	std::mt19937 rng(123);

	std::uniform_real_distribution<double> Distx(bounds.x0, bounds.x1);
	std::uniform_real_distribution<double> Disty(bounds.y0, bounds.y1);
	std::uniform_int_distribution<int> Distm(2, 8);

	for (int i = 0; i < Fractal2::N; i++)
	{
		fractal.GetPoles()[i] = Pole(Distx(rng), Disty(rng), Distm(rng));
	}
	fractal.out(0);

	auto b = std::chrono::steady_clock::now();

	DescendM(1);

	auto e = std::chrono::steady_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(e - b).count() << " ms" << std::endl;
}

