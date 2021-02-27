#pragma once

#include "Fractal2.h"
#include "Optimizer.h"
#include <vector>

class Drawer
{
private:

	const int graphwidth = 800, graphheight = 600;
	const unsigned char black[1] = { 0 };
	const unsigned char gray[1] = { 50 };

	Fractal2& f;
	Optimizer& op;

public:
	Drawer(Fractal2& f, Optimizer& op) : f(f), op(op)
	{
	}

	void Draw();

	void Graph(std::vector<double> x, std::vector<double> y, double xmin, double xmax, double ymin, double ymax);
};

