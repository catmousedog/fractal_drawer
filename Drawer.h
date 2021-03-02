#pragma once

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

	//create and draw the fractal on the new image
	void Draw()
	{
		cimg_library::CImg<unsigned char> img(Fractal2::p, Fractal2::p, 1, 1, 255);
		Draw(img);
		img.display();
	}

	//draw the fractal on the given image
	void Draw(cimg_library::CImg<unsigned char>& img);

	void Graph(std::vector<double> x, std::vector<double> y, double xmin, double xmax, double ymin, double ymax);
};

