#pragma once

#include "main.h"
#define cimg_use_png 1
#include "CImg.h"

double a = 5;
Fractal::Box bounds(-a, -a, a, a);
Fractal fractal(20, 10000, bounds);
Drawer drawer(fractal);

str CMD_Print(deq arg)
{
	fractal.Print();
	std::cout << to_string(fractal.leja.points.size()) << std::endl;
	return "done";
}

str CMD_LejaAdd(deq arg)
{
	if (arg.size() == 0)
	{
		fractal.leja.add(1);
	}
	else
	{
		try
		{
			int m = std::stoi(arg.front());
			fractal.leja.add(m);
		}
		catch (const std::exception&)
		{
			return "except";
		}
	}

	return to_string(fractal.leja.points.size());
}

str CMD_setS(deq arg)
{
	if (arg.size() == 0)
	{
		return to_string(fractal.leja.s);
	}
	else
	{
		try
		{
			double s = std::stod(arg.front());
			fractal.leja.s = s;
			fractal.leja.setConstant();
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
	CImg<unsigned char> img("C:/Users/lauwe/source/repos/FractalDrawer/FractalDrawer/test.png");

#if CONSOLE
	std::map<str, fp> commands;
	commands["print"] = CMD_Print;
	commands["add"] = CMD_LejaAdd;
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
				drawer.Draw();
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

