#pragma once

#include "Util.h"

struct Complex
{
	double x, y;

	Complex() : x(0), y(0)
	{
	}

	Complex(double a) : x(cos(a)), y(sin(a))
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

	inline bool IsZero() const
	{
		return x == 0 && y == 0;
	}

	inline double AbsSquared() const
	{
		return x * x + y * y;
	}

	inline Complex operator-() const
	{
		return Complex(-x, -y);
	}

	inline Complex operator~() const
	{
		return Complex(x, -y);
	}

	inline Complex operator+(const Complex v) const
	{
		return Complex(v.x + x, v.y + y);
	}

	inline Complex operator-(const Complex v) const
	{
		return Complex(v.x - x, v.y - y);
	}

	inline Complex operator*(const double a) const
	{
		return Complex(x * a, y * a);
	}

	inline Complex operator*(const Complex c) const
	{
		return Complex(x * c.x - y * c.y, x * c.y + y * c.x);
	}

	inline Complex operator/(const Complex c) const
	{
		return (*this * (~c)) * (1 / c.AbsSquared());
	}

	inline Complex operator^(const double P) const
	{
		double A = pow(AbsSquared(), P / 2);
		double theta = atan2(y, x);
		return Complex(A * cos(theta * P), A * sin(theta * P));
	}

	inline Complex& operator=(const Complex c)
	{
		x = c.x;
		y = c.y;
		return *this;
	}
	inline Complex& operator+=(const Complex c)
	{
		x += c.x;
		y += c.y;
		return *this;
	}

	inline Complex& operator-=(const Complex c)
	{
		x -= c.x;
		y -= c.y;
		return *this;
	}

	inline Complex& operator*=(const Complex c)
	{
		double tx = x * c.x - y * c.y;
		this->y = x * c.y + y * c.x;
		this->x = tx;
		return *this;
	}

	inline Complex& operator*=(const double a)
	{
		x *= a;
		y *= a;
		return *this;
	}

	inline Complex& operator/=(const Complex c)
	{
		*this = *this / c;
		return *this;
	}

	inline std::string string()
	{
		return to_string(x) + ", " + to_string(y);
	}
};
