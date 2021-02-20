#pragma once

#include "Fractal2.h"
#include <iostream>

Fractal2::Box bounds(-2, -2, 2, 2);
Fractal2 f(50, 10000, bounds);
cimg_library::CImg<unsigned char> img(Fractal2::p, Fractal2::p, 1, 1, 255);

void Draw(Fractal2& fractal, cimg_library::CImg<unsigned char>& img)
{
	unsigned char c = 0;
	unsigned char* t = &c;

	for (int i = 0; i < Fractal2::pixels_size; i++)
	{
		unsigned char c = (unsigned char)(fractal.GetPixels()[i] * 255);
		*t = c;
		img.draw_point(i / Fractal2::p, i % Fractal2::p, t);
	}

	img.display();
}

int main()
{
	f.GetTop()[0] = Pole(1, 0, 1);
	f.GetTop()[1] = Pole(-1, 0, 1);
	f.GetTop()[2] = Pole(0, 1, 1);
	f.GetTop()[3] = Pole(0, -1, 1);

	f.Iterate();

	for (int a=5000; a<6000; a++)
		std::cout << f.GetCoordinates()[a].string() << ", " << f.GetPixels()[a] << ", " << f.Func(f.GetCoordinates()[a]) << std::endl;

	Draw(f, img);
	//unsigned char c = 0;
	//unsigned char* t = &c;
	//for (int i = 0; i < Fractal2::pixels_size; i++)
	//{
	//	unsigned char c = (int)(f.GetPixels()[i] * 255);
	//	*t = c;
	//	img.draw_point(i / Fractal2::p, i % Fractal2::p, t);
	//}

	//img.display();

	return 0;
}