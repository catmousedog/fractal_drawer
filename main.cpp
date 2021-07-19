#pragma once

#include "main.h"

Fractal fractal(100, 1E10);
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
				for (Region* region : fractal.leja.name)
					region->SetN(N);
			}
			else if (arg.size() == 2)
			{
				int r = std::stoi(arg.front());
				fractal.leja.regions.at(r)->SetN(N);
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
				for (Region* region : fractal.leja.name)
					region->SetC(s);
			}
			else if (arg.size() == 2)
			{
				int r = std::stoi(arg.front());
				fractal.leja.regions.at(r)->SetC(s);
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

str CMD_DrawPoints(deq arg)
{
	drawer.DrawPoints = !drawer.DrawPoints;
	drawer.Draw();
	return "done";
}

str CMD_Random(deq arg)
{
	if (fractal.leja.regions.size() > 0)
	{
		fractal.leja.regions.back()->points.clear();
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
	fractal.leja.regions.push_back(&region);
	drawer.Draw();
	return "done";
}

str CMD_Save(deq arg)
{
	fractal.Save();
	return "done";
}

str CMD_Load(deq arg)
{
	fractal.Load();
	drawer.Draw();
	return "done";
}

str CMD_CalculateLeja(deq arg)
{
	fractal.Save();
	for (int i = 0; i < fractal.leja.regions.size(); i++)
	{
		fractal.leja.regions.at(i)->CalculateLeja(i);
	}
	return "done";
}

str CMD_Benchmark(deq arg)
{
	auto begin = std::chrono::steady_clock::now();
	fractal.leja.regions.front()->SetN(10);
	drawer.Draw();
	auto end = std::chrono::steady_clock::now();
	return std::to_string((end - begin).count());
}

str CMD_Console(deq arg)
{
	Console = !Console;
	return "--KEYBOARD--";
}

double scale = 0.7;

int main()
{
	for (int i = 0; i <= 18; i++)
	{
		//LoadCoefficients(i, false);
		//LoadLejaPoints(i, false);
		LoadLejaWithBoundary(i, false);
	}

	//initial origin
	std::vector<Complex> leja;

	//////////////////1
	//leja.push_back(Complex(-10.000000, 0.000000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 5.000000), true);
	//leja.clear();

	//leja.push_back(Complex(31.163894, -7.410710));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 0.400000), true);
	//leja.clear();

	//leja.push_back(Complex(-1.763714, -20.519333));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 0.100000), true);
	//leja.clear();

	//leja.push_back(Complex(25.065012, -23.027710));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 6.000000), true);
	//leja.clear();
	//////////////////

	//////////////////2
	//leja.push_back(Complex(-8.624648, 3.163936));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 5.000000), true);
	//leja.clear();

	//leja.push_back(Complex(41.958030, 0.976577));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 6.000000), true);
	//leja.clear();

	//leja.push_back(Complex(18.952345, -22.183864));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 0.100000), true);
	//leja.clear();

	//leja.push_back(Complex(-42.004567, -17.634841));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 0.100000), true);
	//leja.clear();
	//////////////////

	//////////////////3
	//leja.push_back(Complex(-30.772960, -3.624878));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 5.800000), true);
	//leja.clear();

	//leja.push_back(Complex(31.621544, 15.871715));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 6.200000), true);
	//leja.clear();
	//////////////////

	//////////////////4
	//leja.push_back(Complex(-28.873997, -10.745991));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 5.800000), true);
	//leja.clear();

	//leja.push_back(Complex(31.621544, 15.871715));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 6.200000), true);
	//leja.clear();
	//////////////////

	//////////////////5
	//leja.push_back(Complex(0.750000, 1.100000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 0.700000), true);
	//leja.clear();

	//leja.push_back(Complex(10.000000, -3.900000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 3.500000), true);
	//leja.clear();

	//leja.push_back(Complex(-7.700000, -0.300000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 3.200000), true);
	//leja.clear();
	//////////////////

	//////////////////6
	//leja.push_back(Complex(0.750000, 1.100000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 0.700000), true);
	//leja.clear();

	//leja.push_back(Complex(10.000000, -3.900000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 3.500000), true);
	//leja.clear();

	//leja.push_back(Complex(-7.650000, 0.100000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 3.200000), true);
	//leja.clear();
	//////////////////

	//////////////////7
	//leja.push_back(Complex(0.750000, 1.100000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 0.700000), true);
	//leja.clear();

	//leja.push_back(Complex(10.000000, -3.900000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 3.500000), true);
	//leja.clear();

	//leja.push_back(Complex(-7.500000, -0.150000));
	//fractal.leja.AddRegion(new Region(leja, leja.size(), 3.200000), true);
	//leja.clear();
	//////////////////

	//////////////////8
	leja.push_back(Complex(4.250000, -1.200000));
	fractal.leja.AddRegion(new Region(leja, leja.size(), 2.400000), true);
	leja.clear();

	leja.push_back(Complex(6.650000, 6.350000));
	fractal.leja.AddRegion(new Region(leja, leja.size(), 0.200000), true);
	leja.clear();

	leja.push_back(Complex(15.500000, 0.750000));
	fractal.leja.AddRegion(new Region(leja, leja.size(), 0.100000), true);
	leja.clear();

	leja.push_back(Complex(12.250000, -6.450000));
	fractal.leja.AddRegion(new Region(leja, leja.size(), 0.300000), true);
	leja.clear();
	//////////////////


	Console = false;


	for (Region* region : fractal.leja.name)
	{
		region->s = 0.1;
		region->SetN(10);
	}

	drawer.Draw();

	std::map<str, fp> commands;
	commands["draw"] = CMD_Draw;
	commands["print"] = CMD_Print;
	commands["n"] = CMD_SetN;
	commands["s"] = CMD_SetS;
	commands["save"] = CMD_Save;
	commands["load"] = CMD_Load;
	commands["random"] = CMD_Random;
	commands["draw"] = CMD_DrawPoints;
	commands["calc"] = CMD_CalculateLeja;
	commands["console"] = CMD_Console;

	std::cout << "--CONSOLE--" << std::endl;
	while (!drawer.IsClosed())
	{
		if (Console)
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
		else
		{
			CImgDisplay::wait(drawer.GetDisplay());

			if (drawer.GetDisplay().is_keyESC())
			{
				Console = !Console;
				std::cout << "--CONSOLE--" << std::endl;
			}
			else if (drawer.GetDisplay().is_keySHIFTLEFT())
			{
				shift *= 1.1;
				std::cout << shift << std::endl;
			}
			else if (drawer.GetDisplay().is_keyCTRLLEFT())
			{
				shift *= 0.9;
				std::cout << shift << std::endl;
			}
			//MOVE NAME
			else if (drawer.GetDisplay().is_keyARROWUP())
			{
				fractal.leja.Shift(Complex(0, shift));
				drawer.Draw();
			}
			else if (drawer.GetDisplay().is_keyARROWLEFT())
			{
				fractal.leja.Shift(Complex(-shift, 0));
				drawer.Draw();
			}
			else if (drawer.GetDisplay().is_keyARROWDOWN())
			{
				fractal.leja.Shift(Complex(0, -shift));
				drawer.Draw();
			}
			else if (drawer.GetDisplay().is_keyARROWRIGHT())
			{
				fractal.leja.Shift(Complex(shift, 0));
				drawer.Draw();
			}
			//MOVE BOUNDS
			else if (drawer.GetDisplay().is_keyI())
			{
				fractal.bounds.Shift(Complex(0, shift));
				fractal.SetCoordinates();
				drawer.Draw();
			}
			else if (drawer.GetDisplay().is_keyJ())
			{
				fractal.bounds.Shift(Complex(-shift, 0));
				fractal.SetCoordinates();
				drawer.Draw();
			}
			else if (drawer.GetDisplay().is_keyK())
			{
				fractal.bounds.Shift(Complex(0, -shift));
				fractal.SetCoordinates();
				drawer.Draw();
			}
			else if (drawer.GetDisplay().is_keyL())
			{
				fractal.bounds.Shift(Complex(shift, 0));
				fractal.SetCoordinates();
				drawer.Draw();
			}
			//SCALE BOUNDS
			else if (drawer.GetDisplay().is_keyU())
			{
				fractal.bounds.Scale(0.5);
				fractal.SetCoordinates();
				drawer.Draw();
			}
			else if (drawer.GetDisplay().is_keyO())
			{
				fractal.bounds.Scale(2);
				fractal.SetCoordinates();
				drawer.Draw();
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
			points.push_back(Complex(x, y) * scale);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	segment.close();
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
			coeff.push_back(Complex(x, y) * scale);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	segment.close();
	return coeff;
}

void LoadLejaPoints(int i, bool origin)
{
	fractal.leja.AddRegion(new Region(GetLejaPoints(GetPathLeja(i)), 0, -1), origin);
}

void LoadCoefficients(int i, bool origin)
{
	fractal.leja.AddRegion(new Region(GetCoefficients(GetPathCoeff(i)), -1), origin);
}

void LoadLejaWithBoundary(int i, bool origin)
{
	fractal.leja.AddRegion(new Region(GetCoefficients(GetPathCoeff(i)), GetLejaPoints(GetPathLeja(i)), 0, -1), origin);
}
