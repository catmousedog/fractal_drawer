#pragma once

#include "Fractal.h"
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

	Fractal& f;

public:
	Drawer(Fractal& f) : f(f)
	{
	}

	//create and draw the fractal on the new image
	void Draw()
	{
		cimg_library::CImg<unsigned char> img(Fractal::p, Fractal::p, 1, 3, 255);
		Draw(img);
		img.display();
	}

	//draw the fractal on the given image
	void Draw(cimg_library::CImg<unsigned char>& img);

	void Graph(std::vector<double> x, std::vector<double> y, double xmin, double xmax, double ymin, double ymax);
};

