#pragma once

#include "main.h"

Complex offset(0, 0);
double a = 15;
double X = 0 + offset.x, Y = 0 + offset.y;
//double a = 4;
//double X = 0, Y = 0;
Fractal::Box bounds(X - a, Y - a, X + a, Y + a);
Fractal fractal(25, 1E10, bounds);
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

str CMD_Random(deq arg)
{
	if (fractal.leja.regions.size() > 0)
	{
		fractal.leja.regions.back().leja.clear();
		fractal.leja.regions.pop_back();
	}

	int R = 10;
	try
	{
		if (arg.size() != 0)
		{
			R = std::stoi(arg.front());
		}
	}
	catch (const std::exception&)
	{
		std::cout << "except" << std::endl;
	}

	std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<> dis(-5, 5);
	std::vector<Complex> leja;
	for (int i = 0; i < R; i++)
	{
		leja.push_back(Complex(dis(gen), dis(gen)));
	}
	Region region = Region(leja, leja.size(), 0.05);
	fractal.leja.regions.push_back(region);
	drawer.Draw();
	return "done";
}

str CMD_Save(deq arg)
{
	std::ofstream parameters;
	parameters.open(path + "parameters.txt");
	for (Region& region : fractal.leja.regions)
	{
		parameters << region.N << "," << region.s << "," << region.C << std::endl;
	}
	fractal.Save();
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
			int N = std::stoi(d.at(0));
			double s = std::stod(d.at(1));
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
	std::vector<Complex> leja;
	leja.push_back(Complex(1, 0));
	Region region(leja, leja.size(), 0.1);
	fractal.leja.regions.push_back(region);
	//

	//auto begin = std::chrono::steady_clock::now();
	//fractal.leja.regions.front().SetN(10);
	drawer.Draw();
	//auto end = std::chrono::steady_clock::now();
	//std::cout << (end - begin).count() << std::endl;

	std::map<str, fp> commands;
	commands["draw"] = CMD_Draw;
	commands["print"] = CMD_Print;
	commands["n"] = CMD_SetN;
	commands["s"] = CMD_SetS;
	commands["save"] = CMD_Save;
	commands["load"] = CMD_Load;
	commands["random"] = CMD_Random;

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
