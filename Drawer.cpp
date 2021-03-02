#include "Drawer.h"
#include <assert.h>

void Drawer::Draw(cimg_library::CImg<unsigned char>& img)
{
	unsigned char color[1] = { 0 };

	for (int i = 0; i < Fractal2::pixels_size; i++)
	{
		color[0] = (unsigned char)(f.pixels[i] * 255);
		img.draw_point(i / Fractal2::p, Fractal2::p - i % Fractal2::p, color);
	}

	img.draw_axes((float)f.bounds.x0, (float)f.bounds.x1, (float)f.bounds.y1, (float)f.bounds.y0, gray, 1.0f, 5, 5, 0, 0, ~0u, ~0u, 8);
}

void Drawer::Graph(std::vector<double> X, std::vector<double> Y, double xmin, double xmax, double ymin, double ymax)
{
	assert(X.size() == Y.size());

	cimg_library::CImg<unsigned char> img(graphwidth, graphheight, 1, 1, 255);

	img.draw_axes(xmin, xmax, ymax, ymin, gray, 1.0f, 21, 21, 0, 0, ~0u, ~0u, 8);

	for (int i = 0; i < X.size(); i++)
	{
		img.draw_circle(X.at(i) * graphwidth, graphheight - Y.at(i) * graphheight, 2, black);
	}
	
	img.display();
}