#pragma once

#include "main.h"

double a = 12;
Fractal::Box bounds(-a, -a, a, a);
Fractal fractal(20, 10000, bounds);
Drawer drawer(fractal);

str CMD_Print(deq arg)
{
	//fractal.Print();
	for (Complex c : fractal.region.coefficients)
	{
		std::cout << c.string() << std::endl;
	}
	std::cout << fractal.region.coefficients.size() << std::endl;
	return "done";
}

str CMD_CoeffAdd(deq arg)
{
	if (arg.size() == 2)
	{
		try
		{
			double x = std::stod(arg.front());
			double y = std::stod(arg.back());
			fractal.region.AddCoefficient(Complex(x, y));
		}
		catch (const std::exception&)
		{
			return "except";
		}
	}

	return fractal.region.coefficients.back().string();
}

str CMD_SetN(deq arg)
{
	int N = 0;
	if (arg.size() == 0)
	{
		N = fractal.region.points.size();
	}
	else
	{
		try
		{
			N = std::stoi(arg.front());
			fractal.region.SetPoints(N);
		}
		catch (const std::exception&)
		{
			return "except";
		}
	}
	return std::to_string(N);
}

#define CONSOLE true

int main()
{
	//for (double n = 1; n <= 5; n++)
	//{
	//	fractal.region.AddCoefficient(Complex(log(2*n) / n, 0.0));
	//}
	fractal.region.AddCoefficient(Complex(-0.10080645161290391, 3.214285714285716));
	fractal.region.AddCoefficient(Complex(2.52016129032258, 0.16233766233766223));

#if CONSOLE
	std::map<str, fp> commands;
	commands["print"] = CMD_Print;
	commands["add"] = CMD_CoeffAdd;
	commands["n"] = CMD_SetN;

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

