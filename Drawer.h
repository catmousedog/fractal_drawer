#pragma once

#include "Optimizer.h"
#include "CImg.h"
#include <assert.h>
#include <vector>

class Drawer
{
private:

	const int graphwidth = 800, graphheight = 600;
	const unsigned char black[3] = { 0, 0, 0 };
	const unsigned char gray[3] = { 50, 50, 50 };
	const unsigned char white[3] = { 255, 255, 255 };
	const unsigned char red[3] = { 255, 0, 0 };

	Fractal2& f;
	Optimizer& op;

public:
	Drawer(Fractal2& f, Optimizer& op) : f(f), op(op)
	{
	}

	//create and draw the fractal on the new image
	void Draw()
	{
		cimg_library::CImg<unsigned char> img(Fractal2::p, Fractal2::p, 1, 3, 255);
		Draw(img);
		img.display();
	}

	//draw the fractal on the given image
	void Draw(cimg_library::CImg<unsigned char>& img);

	void Graph(std::vector<double> x, std::vector<double> y, double xmin, double xmax, double ymin, double ymax);
};

