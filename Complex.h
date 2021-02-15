#pragma once

#include "Vector.h"

#ifndef INTEGER_EXPONENT
#define INTEGER_EXPONENT true
#endif

#if INTEGER_EXPONENT
#define EXPONENT_TYPE int
#else
#define EXPONENT_TYPE double
#endif

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
	Complex operator+(const Complex& v) const
	{
		return Complex(v.x + x, v.y + y);
	}
	Complex operator-(const Complex& v) const
	{
		return Complex(v.x - x, v.y - y);
	}
	Complex operator*(const double a) const
	{
		return Complex(x * a, y * a);
	}
	Complex operator*(const Complex& c) const
	{
		return Complex(x * c.x - y * c.y, x * c.y + y * c.x);
	}
	Complex operator/(const Complex& c) const
	{
		return (*this * (~c)) * (1 / c.AbsSquared());
	}
	Complex operator^(const double P) const
	{
		double A = exp(P * log(AbsSquared()) / 2);
		double theta = atan2(y, x);
		return Complex(A * cos(theta * P), A * sin(theta * P));
	}
	Complex operator^(const int P) const
	{
		if (P > 0)
		{
			Complex c(*this);
			for (int i = 0; i < P - 1; i++)
				c *= *this;
			return c;
		}
		else if (P < 0)
		{
			Complex c(1, 0);
			for (int i = 0; i < -P; i++)
				c /= *this;
			return c;
		}
		else // P==0
		{
			return Complex(1, 0);
		}
	}
	Complex& operator+=(const Complex& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Complex& operator*=(const Complex& c)
	{
		*this = *this * c;
		return *this;
	}
	Complex& operator/=(const Complex& c)
	{
		*this = *this / c;
		return *this;
	}
	std::string string()
	{
		return "c: " + std::to_string(x) + " | " + std::to_string(y);
	}
};

struct Pole : Complex
{
	EXPONENT_TYPE m;

	Pole() : m(EXPONENT_TYPE(0))
	{
	}
	Pole(double X, double Y, EXPONENT_TYPE M) : Complex(X, Y), m(M)
	{
	}
	Pole(const Pole& p) : Complex(p), m(p.m)
	{
	}

	//evaluates a complex number in the polynomial belonging to this pole
	Complex poly(Complex& q) const
	{
		q += -*this;
		return q ^ m;
	}
	Pole operator+(const Vector& v)
	{
		return Pole(x + v.x, y + v.y, m);
	}
	Pole& operator+=(const Vector& v)
	{
		*this = *this + v;
		return *this;
	}
	inline std::string string()
	{
		return "poles.add(new Pole(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(m) + "));";
	}
};
