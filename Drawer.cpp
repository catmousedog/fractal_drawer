#pragma once

#include "Drawer.h"

void Drawer::Draw(cimg_library::CImg<unsigned char>& img)
{
	unsigned char color[3] = { 0, 0, 0 };

	for (int i = 0; i < Fractal::pixels_size; i++)
	{
		unsigned char c = (unsigned char)(f.pixels[i] * 255);
		color[0] = c;
		color[1] = c;
		color[2] = c;
		img.draw_point(i / Fractal::p, Fractal::p - i % Fractal::p, color);
		//double d = op.desired[i];
		//if (d == 0)
		//{
		//	color[0] = (unsigned char)(255.0);
		//	color[1] = 0;
		//	color[2] = 0;
		//	img.draw_point(i / Fractal::p, Fractal::p - i % Fractal::p, color, 0.3f);
		//}
	}

	img.draw_axes((float)f.bounds.x0, (float)f.bounds.x1, (float)f.bounds.y1,
		(float)f.bounds.y0, gray, 1.0f, 5, 5, 0, 0, ~0u, ~0u, 8);

	for (int i = 0; i < Fractal::N; i++)
	{
		//int x = (int)(Fractal::p * (f.poles[i].x - f.bounds.x0) / f.bounds.Width());
		//int y = (int)(Fractal::p * (f.poles[i].y - f.bounds.y0) / f.bounds.Height());
		//img.draw_circle(x, y, 2, red, 0.5f);
	}
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