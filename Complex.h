#pragma once

#include "Vector.h"

struct Complex
{
	double x, y;

	Complex() : x(0), y(0)
	{
	}

	Complex(double x_, double y_) : x(x_), y(y_)
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
		//double A = exp(P * log(AbsSquared()) / 2);
		double A = pow(AbsSquared(), P / 2);
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
		else
		{
			Complex c(1, 0);
			for (int i = 0; i < -P; i++)
				c /= *this;
			return c;
		}
	}

	Complex& operator=(const Complex& c)
	{
		x = c.x;
		y = c.y;
		return *this;
	}
	Complex& operator+=(const Complex& c)
	{
		x += c.x;
		y += c.y;
		return *this;
	}

	Complex& operator-=(const Complex& c)
	{
		*this += -c;
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
		return std::to_string(x) + ", " + std::to_string(y);
	}
};

struct Pole : Complex
{

	int m;

	Pole() : m(0)
	{
	}

	Pole(double x_, double y_, int m_) : Complex(x_, y_), m(m_)
	{
	}

	Pole(const Pole& p) : Complex(p), m(p.m)
	{
	}

	//evaluates a complex number in the polynomial belonging to this pole
	Complex poly(Complex q, const int a) const
	{
		q -= *this;
		return q ^ (a * m);
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
		return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(m);
		//return "poles.add(new Pole(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(m) + "));";
	}

};

struct Top : Pole
{
	Top()
	{
	}

	Top(double x, double y, int m) : Pole(x, y, abs(m))
	{
	}

	Top(const Top& p) : Pole(p.x, p.y, abs(p.m))
	{
	}
};

struct Bottom : Pole
{
	Bottom()
	{
	}

	Bottom(double x, double y, int m) : Pole(x, y, -abs(m))
	{
	}

	Bottom(const Bottom& p) : Pole(p.x, p.y, -abs(p.m))
	{
	}
};
