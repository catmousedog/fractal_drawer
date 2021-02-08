#pragma once

#include "Vector.h"

struct Complex
{
	float x, y;

	Complex() : x(0), y(0)
	{
	}
	Complex(float X, float Y) : x(X), y(Y)
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
	float AbsSquared() const
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
	Complex operator^(const float P) const
	{
		float A = exp(P * log(AbsSquared()) / 2);
		float theta = atan2(y, x);
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
		float tx = x * c.x - y * c.y;
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
	float m;

	Pole() : m(0)
	{
	}
	Pole(float X, float Y, float M) : Complex(X, Y), m(M)
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
		return "p: " + std::to_string(x) + " | " + std::to_string(y) + " | " + std::to_string(m);
	}
};
