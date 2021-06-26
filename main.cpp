#pragma once

#include "main.h"

double a = 20;
double X = 0, Y = 15;
Fractal::Box bounds(X - a, Y - a, X + a, Y + a);
Fractal fractal(20, 10000, bounds);
Drawer drawer(fractal);

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

str CMD_setS(deq arg)
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

Complex offset(-10, 12);
Complex offsets[] = {
					Complex(0, 0), Complex(0, 0) , Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0),
					Complex(10, 0), Complex(10, 0), Complex(10, 0), Complex(10, 0),
					Complex(20, 0), Complex(20, 0), Complex(20, 0),
					Complex(28, 0), Complex(28, 0), Complex(28, 0), Complex(28, 0) };

str path = "C:\\Users\\Gebruiker\\source\\repos\\FractalDrawer\\FractalDrawer\\data\\";

int main()
{
	//LoadCoefficients(path + "coeff\\segment_.txt", Complex() + offset);
	LoadLejaPoints(path + "leja\\segment_.txt", offset);
	for (int i = 11; i <= 12; i++)
	{
		//LoadCoefficients(path + "coeff\\segment_" + to_string(i) + ".txt", offsets[i] + offset);
		//LoadLejaPoints(path + "leja\\segment_" + to_string(i) + ".txt", offsets[i] + offset);
	}

	//origin
	std::vector<Complex> coeff;
	coeff.push_back(Complex(1, 0));
	coeff.push_back(Complex(0, 0));
	Region region = Region(coeff, Complex(0, 0), 0.01);
	fractal.leja.regions.push_back(region);
	//

	drawer.Draw();

	std::map<str, fp> commands;
	commands["print"] = CMD_Print;
	commands["n"] = CMD_SetN;
	commands["s"] = CMD_setS;

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

void LoadLejaPoints(str file, Complex offset)
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
	fractal.leja.regions.push_back(Region(points, 30, 0.04));
}

void LoadCoefficients(str file, Complex offset)
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
	fractal.leja.regions.push_back(Region(coeff, offset, 0.01));
}


