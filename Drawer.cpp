#pragma once

#include "Drawer.h"

void Drawer::Draw()
{
	fractal.Iterate();
	CImg<unsigned char> img(Fractal::p, Fractal::p, 1, 3, 255);

	unsigned char color[3] = { 0, 0, 0 };
	for (int i = 0; i < Fractal::pixels_size; i++)
	{
		unsigned char c = (unsigned char)(fractal.pixels[i] * 255);
		color[0] = c;
		color[1] = c;
		color[2] = c;
		img.draw_point(i / Fractal::p, Fractal::p - i % Fractal::p, color);
	}

	img.draw_axes((float)fractal.bounds.x0, (float)fractal.bounds.x1, (float)fractal.bounds.y1,
		(float)fractal.bounds.y0, gray, 1.0f, 5, 5, 0, 0, ~0u, ~0u, 8);


	for (Complex b : fractal.region.points)
	{
		int x = (int)(Fractal::p * (b.x - fractal.bounds.x0) / fractal.bounds.Width());
		int y = (int)(Fractal::p - Fractal::p * (b.y - fractal.bounds.y0) / fractal.bounds.Height());
		img.draw_circle(x, y, 2, red, 0.5f);
	}

	for (Complex p : fractal.region.coefficients)
	{
		int x = (int)(Fractal::p * (p.x - fractal.bounds.x0) / fractal.bounds.Width());
		int y = (int)(Fractal::p - Fractal::p * (p.y - fractal.bounds.y0) / fractal.bounds.Height());
		img.draw_circle(x, y, 2, blue, 1.0f);
	}

	dsp.display(img);
}
