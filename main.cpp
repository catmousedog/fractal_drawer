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

int main()
{
	//pre console start


	//console start
	std::map<str, fp> commands;
	commands["print"] = CMD_Print;
	commands["draw"] = CMD_Draw;

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

	return 0;
}
