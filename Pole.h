#pragma once

#include "Complex.h"

struct Pole : Complex
{
	float x, y, m;
	//log(|pole|)
	double logz;
	float theta;

	void Set(const float X, const float Y)
	{
		x = X;
		y = Y;
		logz = log((double)x * x + (double)y * y);
		theta = atan2(y, x);
	}

	//Pole operator-(const Pole c)
	//{
	//	return Pole(x - c.x, y - c.y, m);
	//}
	Complex operator^(const float P) const
	{
		Complex c;
		float A = exp(P * logz / 2);
		c.x = A * cos(theta * P);
		c.y = A * sin(theta * P);
		return c;
	}
	Complex operator^(const int P) const
	{
		Complex c(x, y);
		for (int i = 0; i < P - 1; i++)
		{
			c *= c;
		}
		return c;
	}
	Complex& operator+=(const Complex c)
	{
		x += c.x;
		y += c.y;
		return *this;
	}
	Complex& operator*=(const Complex c)
	{
		float tx = x;
		x *= x * c.x - y * c.y;
		y *= tx * c.y + y * c.x;
		return *this;
	}
	std::string string()
	{
		return std::to_string(x) + " | " + std::to_string(y);
	}

	//evaluates a complex number in the polynomial belonging to this pole
	inline Complex poly(const Complex q) const
	{
		return (q - *this) ^ m;
	}
	Pole() : m(0), logz(0), theta(0)
	{
		Set(0, 0);
	}
	Pole(int X, int Y, float M) : m(M)
	{
		Set(X, Y);
	}
	//copy contstructor
	Pole(const Pole& p) : m(p.m), logz(p.logz), theta(p.theta)
	{
		Set(p.x, p.y);
	}
	inline std::string string()
	{
		return "p: " + std::to_string(x) + " | " + std::to_string(y) + " | " = std::to_string(m);
	}
};
