#pragma once

#include "main.h"

double a = 22;
double X = 0, Y = 12;
Fractal::Box bounds(X - a, Y - a, X + a, Y + a);
Fractal fractal(20, 10000, bounds);
Drawer drawer(fractal);

str CMD_Draw(deq arg)
{
	drawer.Draw();
	return "done";
}

str CMD_Print(deq arg)
{
	std::cout << fractal.leja.GetN() << std::endl;
	std::cout << fractal.leja.GetS() << std::endl;
	return "done";
}

str CMD_SetN(deq arg)
{
	try
	{
		if (arg.size() > 0)
		{
			int N = std::stoi(arg.back());
			if (arg.size() == 1)
			{
				for (Region& region : fractal.leja.regions)
					region.SetN(N);
			}
			else if (arg.size() == 2)
			{
				int r = std::stoi(arg.front());
				fractal.leja.regions.at(r).SetN(N);
			}
			drawer.Draw();
		}
	}
	catch (const std::exception&)
	{
		return "except";
	}

	return fractal.leja.GetN();
}

str CMD_SetS(deq arg)
{
	try
	{
		if (arg.size() > 0)
		{
			double s = std::stod(arg.back());
			if (arg.size() == 1)
			{
				for (Region& region : fractal.leja.regions)
					region.SetC(s);
			}
			else if (arg.size() == 2)
			{
				int r = std::stoi(arg.front());
				fractal.leja.regions.at(r).SetC(s);
			}
			drawer.Draw();
		}
	}
	catch (const std::exception&)
	{
		return "except";
	}

	return fractal.leja.GetS();
}

str CMD_Save(deq arg)
{
	std::ofstream parameters;
	parameters.open(path + "parameters.txt");
	for (Region& region : fractal.leja.regions)
	{
		parameters << region.s << "," << region.N << std::endl;
	}
	return "done";
}

str CMD_Load(deq arg)
{
	std::ifstream parameters;
	parameters.open(path + "parameters.txt");
	str line;
	for (int i = 0; std::getline(parameters, line); i++)
	{
		deq d = split(line, ',');
		try
		{
			double s = std::stod(d.front());
			int N = std::stoi(d.back());
			fractal.leja.regions.at(i).s = s;
			fractal.leja.regions.at(i).SetN(N); //SetC
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	drawer.Draw();
	return "done";
}

int main()
{
	for (int i = 0; i <= 17; i++)
	{
		//LoadCoefficients(i);
		//LoadLejaPoints(i);
		LoadLejaWithBoundary(i);
	}

	//origin
	std::vector<Complex> coeff;
	coeff.push_back(Complex(1, 0));
	coeff.push_back(Complex(-2, 0));
	Region region = Region(coeff, Complex(), 0.01);
	region.SetN(10);
	fractal.leja.regions.push_back(region);
	//

	drawer.Draw();

	std::map<str, fp> commands;
	commands["draw"] = CMD_Draw;
	commands["print"] = CMD_Print;
	commands["n"] = CMD_SetN;
	commands["s"] = CMD_SetS;
	commands["save"] = CMD_Save;
	commands["load"] = CMD_Load;

	std::cout << "--CONSOLE--" << std::endl;
	while (!drawer.IsClosed())
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
				str message = f(words);
				std::cout << message << std::endl;
			}
		}
	}
	return 0;
}

std::vector<Complex> GetLejaPoints(str file)
{
	std::ifstream segment;
	segment.open(file);

	std::vector<Complex> points;
	str line;
	while (std::getline(segment, line))
	{
		deq d = split(line, ',');
		try
		{
			double x = std::stod(d.front());
			double y = std::stod(d.back());
			points.push_back(Complex(x, y) + offset);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return points;
}

std::vector<Complex> GetCoefficients(str file)
{
	std::ifstream segment;
	segment.open(file);

	std::vector<Complex> coeff;
	str line;
	while (std::getline(segment, line))
	{
		deq d = split(line, ',');
		try
		{
			double x = std::stod(d.front());
			double y = std::stod(d.back());
			coeff.push_back(Complex(x, y));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return coeff;
}

void LoadLejaPoints(int i)
{
	fractal.leja.regions.push_back(Region(GetLejaPoints(GetPathLeja(i)), 0, -1));
}

void LoadCoefficients(int i)
{
	fractal.leja.regions.push_back(Region(GetCoefficients(GetPathCoeff(i)), offset, -1));
}

void LoadLejaWithBoundary(int i)
{
	fractal.leja.regions.push_back(Region(GetCoefficients(GetPathCoeff(i)), offset, GetLejaPoints(GetPathLeja(i)), 0, -1));
}
