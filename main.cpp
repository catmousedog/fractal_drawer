#pragma once

#include "main.h"
#define cimg_use_png 1
#include "CImg.h"

double a = 6;
Fractal::Box bounds(-a, -a, a, a);
Fractal fractal(20, 10000, bounds);
Drawer drawer(fractal);

str CMD_Print(deq arg)
{
	fractal.Print();
	std::cout << "N= " << to_string(fractal.leja.N) << std::endl;
	return "done";
}

str CMD_SetN(deq arg)
{
	if (arg.size() == 2)
	{
		try
		{
			int r = std::stoi(arg.front());
			int N = std::stoi(arg.back());
			fractal.leja.regions.at(r).SetN(N);
			drawer.Draw();
		}
		catch (const std::exception&)
		{
			return "except";
		}
	}

	return "";
}

str CMD_setS(deq arg)
{
	if (arg.size() == 0)
	{
		str s;
		for (Leja::Region& region : fractal.leja.regions)
		{
			s += to_string(region.s) + "\n";
		}
		return s;
	}
	else
	{
		try
		{
			double s = std::stod(arg.front());
			for (Leja::Region& region : fractal.leja.regions)
			{
				region.setConstant(s);
			}
			drawer.Draw();
		}
		catch (const std::exception&)
		{
			return "except";
		}
	}
	return "done";
}

#define CONSOLE true

int main()
{
#if CONSOLE
	std::map<str, fp> commands;
	commands["print"] = CMD_Print;
	commands["add"] = CMD_SetN;
	commands["s"] = CMD_setS;

	drawer.Draw();

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
#else
#define INTERACTIVE true
	fractal.Iterate();
	drawer.Draw();

	auto prev = std::chrono::steady_clock::now();
	while (!drawer.IsClosed())
	{
#if INTERACTIVE
		CImgDisplay::wait(drawer.GetDisplay());

		if (drawer.GetDisplay().is_keyARROWUP())
		{
			fractal.leja.s += 0.01;
			fractal.leja.setConstant();
		}
		else if (drawer.GetDisplay().is_keyARROWDOWN())
		{
			fractal.leja.s -= 0.01;
			fractal.leja.setConstant();
	}
		drawer.Draw();
#else
		auto now = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(now - prev).count() > 1E3)
		{
			prev = now;
			fractal.leja.add();
			drawer.Draw();
		}
#endif
}
#endif
	return 0;
}

