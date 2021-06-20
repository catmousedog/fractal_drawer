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
			drawer.Draw();
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
			drawer.Draw();
		}
		catch (const std::exception&)
		{
			return "except";
		}
	}
	return std::to_string(N);
}

str CMD_SetCA(deq arg)
{
	Complex CA;
	if (arg.size() == 0)
	{
		CA = fractal.region.CA;
	}
	else 
	{
		try
		{
			double x = std::stod(arg.front());
			double y = 0;
			if (arg.size() > 1)
				y = std::stod(arg.back());
			CA = Complex(x, y);
			fractal.region.setCA(CA);
			drawer.Draw();
		}
		catch (const std::exception&)
		{
			return "except";
		}
		
	}
	return CA.string();
}

#define CONSOLE true

int main()
{
	//for (double n = 1; n <= 5; n++)
	//{
	//	fractal.region.AddCoefficient(Complex(log(2*n) / n, 0.0));
	//}
	fractal.region.AddCoefficient(Complex(0.8246937381859091, 3.690060027651251));
	fractal.region.AddCoefficient(Complex(1.178902595987121, 0.6354877005955134));
	fractal.region.AddCoefficient(Complex(-0.8648782093482568, -0.7947303857150059));
	fractal.region.AddCoefficient(Complex(1.5605068121540981, 1.1735034742121042));
	fractal.region.AddCoefficient(Complex(0.9391367617250453, -0.07934521179576949));
	fractal.region.AddCoefficient(Complex(1.4108436439453311, 0.23882646476667074));
	fractal.region.AddCoefficient(Complex(0.2653298508938929, 0.5880367577014516));
	fractal.region.AddCoefficient(Complex(-0.14579423978993555, 0.2298225326387807));
	fractal.region.AddCoefficient(Complex(-0.22845836027157843, 0.005623617647601732));

#if CONSOLE
	std::map<str, fp> commands;
	commands["print"] = CMD_Print;
	commands["add"] = CMD_CoeffAdd;
	commands["n"] = CMD_SetN;
	commands["ca"] = CMD_SetCA;

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

