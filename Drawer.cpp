#include "Drawer.h"
#include "CImg.h"
#include <assert.h>
#include <iostream>

void Drawer::Draw()
{
	cimg_library::CImg<unsigned char> img(Fractal2::p, Fractal2::p, 1, 1, 255);

	unsigned char color[1] = { 0 };

	for (int i = 0; i < Fractal2::pixels_size; i++)
	{
		color[0] = (unsigned char)(f.pixels[i] * 255);
		img.draw_point(i / Fractal2::p, Fractal2::p - i % Fractal2::p, color);
	}

	img.display();
}

void Drawer::Graph(std::vector<double> X, std::vector<double> Y, double xmin, double xmax)
{
	assert(X.size() == Y.size());

	cimg_library::CImg<unsigned char> img(graphwidth, graphheight, 1, 1, 255);

	img.draw_axes(xmin, xmax, 1, -1, black, 0.5f, 20, 20);

	for (int i = 0; i < X.size(); i++)
	{
		img.draw_circle(X.at(i) * graphwidth, - Y.at(i) * graphheight, 1, black);
	}

	img.display();
}