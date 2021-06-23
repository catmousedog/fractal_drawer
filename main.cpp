#pragma once

#include "main.h"

double a = 15;
Fractal::Box bounds(-a, -a, a, a);
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
			int r = 0;
			int N = std::stoi(arg.back());
			if (arg.size() == 2)
				r = std::stoi(arg.front());
			fractal.leja.regions.at(r).SetN(N);
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
			int r = 0;
			double s = std::stod(arg.back());
			if (arg.size() == 2)
				r = std::stoi(arg.front());
			fractal.leja.regions.at(r).SetC(s);
			drawer.Draw();
		}
	}
	catch (const std::exception&)
	{
		return "except";
	}

	return fractal.leja.GetS();
}

int main()
{
	LoadCoefficients("C:\\Users\\Gebruiker\\Desktop\\CPP\\data\\coeff\\segment_.txt");
	for (int i = 0; i < 2; i++)
	{
		//LoadCoefficients("C:\\Users\\Gebruiker\\Desktop\\CPP\\data\\coeff\\segment_" + to_string(i) + ".txt");
		//LoadLejaPoints("C:\\Users\\Gebruiker\\Desktop\\CPP\\data\\leja\\segment_" + to_string(i) + ".txt");
	}

	//origin
	std::vector<Complex> coeff;
	coeff.push_back(Complex(1, 0));
	coeff.push_back(Complex(0, 0));
	Region region = Region(coeff, 0.1);
	region.AddN(20);
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

#define OFFSETX -5
#define OFFSETY 5

void LoadLejaPoints(str file)
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
			double x = std::stod(d.front()) + OFFSETX;
			double y = std::stod(d.back()) + OFFSETY;
			points.push_back(Complex(x, y));
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	fractal.leja.regions.push_back(Region(points, 10, 0.1));
}

void LoadCoefficients(str file)
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
	fractal.leja.regions.push_back(Region(coeff, 0.1));
}


