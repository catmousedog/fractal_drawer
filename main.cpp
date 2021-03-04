#pragma once

#include "main.h"

double a = 2;
Fractal2::Box bounds(-a, -a, a, a);
Fractal2 fractal(20, 10000, bounds);
Optimizer optimizer(fractal);
Drawer drawer(fractal, optimizer);
Randomizer random(fractal, optimizer, -2, 8);

str CMD_Step(deq arg)
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

str CMD_Pole(deq arg)
{
	if (arg.size() == 4)
	{
		try
		{
			int i = std::stoi(arg.at(0));
			double x = std::stod(arg.at(1));
			double y = std::stod(arg.at(2));
			int m = std::stoi(arg.at(3));
			fractal.GetPoles()[i].x = x;
			fractal.GetPoles()[i].y = y;
			fractal.GetPoles()[i].m = m;
		}
		catch (const std::exception&)
		{
		}
	}
	return "done";
}

str CMD_Random(deq arg)
{
	if (arg.size() == 1)
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
	else if (arg.size() == 2)
	{
		try
		{
			int a = std::stoi(arg.at(1));
			if (arg.at(0) == "exp")
			{

				random.RandomizeE(a);
			}
			else if (arg.at(0) == "pos")
			{
				random.RandomizeP(a);
			}
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

str CMD_Iterate(deq arg)
{
	fractal.Iterate();
	return "done";
}

str CMD_Descend(deq arg)
{
	if (Descend(0) != 0)
		return "changed";
	return "unchanged";
}

str CMD_DescendM(deq arg)
{
	bool changed = false;
	if (arg.size() == 1)
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

str CMD_Train(deq arg)
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

str CMD_Print(deq arg)
{
	fractal.Iterate();
	double E = optimizer.NormEnergy();
	if (arg.size() > 0 && arg.front() == "file")
	{
		fractal.Print(E);
		return "printed to file";
	}
	fractal.out(E);
	return "printed to console";
}

str CMD_Draw(deq arg)
{
	fractal.Iterate();
	drawer.Draw();
	return "";
}

int main()
{
	//pre console start
	//fractal.GetPoles()[0] = Pole(-0.060000, -1.230000, 1.000000);
	//fractal.GetPoles()[1] = Pole(-0.880000, -0.750000, 1.000000);
	//fractal.GetPoles()[2] = Pole(-0.040000, 0.330000, 1.000000);
	//fractal.GetPoles()[3] = Pole(0.490000, -0.510000, 1.000000);
	//fractal.GetPoles()[4] = Pole(1.190000, -1.210000, 1.000000);
	//fractal.GetPoles()[5] = Pole(0.810000, -0.290000, 1.000000);
	//fractal.GetPoles()[6] = Pole(-1.070000, 1.050000, 1.000000);
	//fractal.GetPoles()[7] = Pole(-1.690000, 0.870000, 1.000000);
	//fractal.GetPoles()[8] = Pole(-0.480000, 1.120000, 1.000000);
	//fractal.GetPoles()[9] = Pole(0.030000, 0.970000, 1.000000);
	//fractal.GetPoles()[10] = Pole(1.160000, -0.560000, 1.000000);
	//fractal.GetPoles()[11] = Pole(1.460000, -0.860000, 1.000000);
	//fractal.GetPoles()[12] = Pole(0.810000, -0.960000, 1.000000);
	//fractal.GetPoles()[13] = Pole(0.210000, -0.130000, 1.000000);
	//fractal.GetPoles()[14] = Pole(-0.390000, 0.150000, 1.000000);
	//fractal.GetPoles()[15] = Pole(-0.950000, -0.180000, 1.000000);
	//fractal.GetPoles()[16] = Pole(-0.500000, -1.030000, 1.000000);
	//fractal.GetPoles()[17] = Pole(-0.410000, 0.620000, 1.000000);
	//fractal.GetPoles()[18] = Pole(-0.730000, 0.860000, 1.000000);
	//fractal.GetPoles()[19] = Pole(-1.410000, 1.150000, 1.000000);
	//fractal.GetPoles()[20] = Pole(-0.260000, -0.540000, -1.000000);
	//fractal.GetPoles()[21] = Pole(1.060000, -0.770000, -1.000000);
	//fractal.GetPoles()[22] = Pole(-1.070000, 0.470000, -1.000000);
	//fractal.GetPoles()[23] = Pole(0.020000, 0.670000, -1.000000);
	//fractal.GetPoles()[24] = Pole(0.410000, 0.670000, 1.000000);
	//fractal.GetPoles()[25] = Pole(0.590000, 0.180000, -1.000000);
	random(10);

	//console start
	std::map<str, fp> commands;
	commands["step"] = CMD_Step;
	commands["pole"] = CMD_Pole;
	commands["random"] = CMD_Random;
	commands["iterate"] = CMD_Iterate;
	commands["descend"] = CMD_Descend;
	commands["descendm"] = CMD_DescendM;
	commands["train"] = CMD_Train;
	commands["print"] = CMD_Print;
	commands["draw"] = CMD_Draw;

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
	int terminate = 0;
	for (int i = 0; i < M; i++)
	{
		std::cout << M - i << std::endl;
		terminate = Descend(terminate);
		if (terminate >= Fractal2::N)
			return false;
	}
	return true;
}


int Descend(int terminate)
{
	Pole gradient[Fractal2::N];
	Pole* poles = fractal.GetPoles();

	//calculate current energy
	fractal.Iterate();
	double E = optimizer.Energy();

	std::cout << E << std::endl;

	for (int i = 0; i < Fractal2::N; i++)
	{
		//x
		double gradx = optimizer.GradientX(i, E);
		//y
		double grady = optimizer.GradientY(i, E);
		//exponent
		int gradm = optimizer.GradientE(i, E);

		if (gradx == 0 && grady == 0 && gradm == 0)
			terminate++;
		else
			terminate = 0;
		gradient[i].x = gradx;
		gradient[i].y = grady;
		gradient[i].m = gradm;

		std::cout << i << " += (" << gradx << ", " << grady << ", " << gradm << ")\n";
		if (terminate >= Fractal2::N)
		{
			std::cout << "terminate" << std::endl;
			break;
		}
		
	}

	//add gradient
	for (int i = 0; i < Fractal2::N; i++)
		poles[i] += gradient[i];

	return terminate;
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
	//std::mt19937 rng(123);

	//std::uniform_real_distribution<double> Distx(bounds.x0, bounds.x1);
	//std::uniform_real_distribution<double> Disty(bounds.y0, bounds.y1);
	//std::uniform_int_distribution<int> Distm(2, 8);

	//for (int i = 0; i < Fractal2::N; i++)
	//{
	//	fractal.GetPoles()[i] = Pole(Distx(rng), Disty(rng), Distm(rng));
	//}
	//fractal.out(0);

	//auto b = std::chrono::steady_clock::now();

	//DescendM(1);

	//auto e = std::chrono::steady_clock::now();

	//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(e - b).count() << " ms" << std::endl;
}

