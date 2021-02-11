#pragma once

#include "Vector.h"

struct Complex
{
	double x, y;

	Complex() : x(0), y(0)
	{
	}
	Complex(double X, double Y) : x(X), y(Y)
	{
	}
	Complex(const Complex& c)
	{
		x = c.x;
		y = c.y;
	}

	bool IsZero() const
	{
		return x == 0 && y == 0;
	}
	double AbsSquared() const
	{
		return x * x + y * y;
	}
	Complex operator-() const
	{
		return Complex(-x, -y);
	}
	Complex operator~() const
	{
		return Complex(x, -y);
	}
	Complex operator+(const Complex v) const
	{
		return Complex(v.x + x, v.y + y);
	}
	Complex operator-(const Complex v) const
	{
		return Complex(v.x - x, v.y - y);
	}
	Complex operator*(const Complex c) const
	{
		return Complex(x * c.x - y * c.y, x * c.y + y * c.x);
	}
	Complex operator/(const Complex c) const
	{
		return *this * ~c / Complex(c.AbsSquared(), 0);
	}
	Complex operator^(const double P) const
	{
		double A = exp(P * log(AbsSquared()) / 2);
		double theta = atan2(y, x);
		return Complex(A * cos(theta * P), A * sin(theta * P));
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
	Complex& operator+=(const Complex v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Complex& operator*=(const Complex c)
	{
		double tx = x * c.x - y * c.y;
		y = x * c.y + y * c.x;
		x = tx;
		return *this;
	}
	std::string string()
	{
		return "c: " + std::to_string(x) + " | " + std::to_string(y);
	}
};


struct Pole : Complex
{
	double m;

	Pole() : m(0)
	{
	}
	Pole(double X, double Y, double M) : Complex(X, Y), m(M)
	{
	}
	Pole(const Pole& p) : Complex(p), m(p.m)
	{
	}

	//evaluates a complex number in the polynomial belonging to this pole
	Complex poly(Complex q) const
	{
		q += -*this;
		return q ^ m;
	}
	Pole operator+(const Vector v)
	{
		return Pole(x + v.x, y + v.y, m);
	}
	inline std::string string()
	{
		return "poles.add(new Pole(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(m) + "));";
	}
};
