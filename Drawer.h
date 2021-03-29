#pragma once

#include "Fractal.h"
#include "CImg.h"

using namespace cimg_library;

class Drawer
{
private:

	const int graphwidth = 800, graphheight = 600;
	static constexpr unsigned char black[3] = { 0, 0, 0 };
	static constexpr unsigned char gray[3] = { 50, 50, 50 };
	static constexpr unsigned char white[3] = { 255, 255, 255 };
	static constexpr unsigned char red[3] = { 255, 0, 0 };
	static constexpr unsigned char blue[3] = { 0, 0, 255 };

	Fractal& f;

public:
	Drawer(Fractal& f) : f(f)
	{
	}

	//create and draw the fractal on the new image
	void Draw()
	{
		CImg<unsigned char> img(Fractal::p, Fractal::p, 1, 3, 255);
		Draw(img);
		img.display();
	}

	//draw the fractal on the given image
	void Draw(CImg<unsigned char>& img);

	void Graph(std::vector<double> x, std::vector<double> y, double xmin, double xmax, double ymin, double ymax);
};

