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

	CImgDisplay dsp;

public:
	Drawer(Fractal& f) : f(f), dsp(Fractal::p, Fractal::p, 0)
	{
	}

	void Draw();

	void Graph(std::vector<double> x, std::vector<double> y, double xmin, double xmax, double ymin, double ymax);

	bool IsClosed()
	{
		return dsp.is_closed();
	}

	CImgDisplay& GetDisplay()
	{
		return dsp;
	}
};

