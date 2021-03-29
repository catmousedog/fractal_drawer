#pragma once

#include "main.h"

double a = 2;
Fractal::Box bounds(-a, -a, a, a);
Fractal fractal(20, 10000, bounds);
Drawer drawer(fractal);

str CMD_Print(deq arg)
{
	fractal.Iterate();
	fractal.Print();
	return "done";
}

str CMD_Draw(deq arg)
{
	fractal.Iterate();
	drawer.Draw();
	return "";
}

str CMD_LejaAdd(deq arg)
{
	if (arg.size() == 0)
	{
		fractal.leja.add();
	}
	else
	{
		try
		{
			int m = std::stoi(arg.front());
			for (int i = 0; i < m; i++)
			{
				fractal.leja.add();
			}
			fractal.leja.setConstant();
		}
		catch (const std::exception&)
		{
			return "except";
		}
	}

	return "done";
}

str CMD_setS(deq arg)
{
	if (arg.size() == 0)
	{
		std::cout << fractal.leja.s << std::endl;
	}
	else
	{
		try
		{
			double s = std::stod(arg.front());
			fractal.leja.s = s;
			fractal.leja.setConstant();
			return to_string(s);
		}
		catch (const std::exception&)
		{
			return "except";
		}
	}
	return "";
}

str CMD_C(deq arg)
{
	return to_string(fractal.leja.C);
}

int main()
{
	Img();
	//Console();
	return 0;
}

void Img()
{
	CImg<unsigned char> img(Fractal::p, Fractal::p, 1, 3, 255);
	CImgDisplay disp(img);

	// Main display loop
	while (!disp.is_closed() && !disp.is_keyQ() && !disp.is_keyESC()) {

		CImgDisplay::wait(disp);

		// When clicking on the image
		if (disp.button()) {
			int x = disp.mouse_x();
			int y = disp.mouse_y();

		}
	}
}

void Console()
{
	
	//console start
	std::map<str, fp> commands;
	commands["print"] = CMD_Print;
	commands["draw"] = CMD_Draw;
	commands["add"] = CMD_LejaAdd;
	commands["s"] = CMD_setS;
	commands["c"] = CMD_C;

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
}
