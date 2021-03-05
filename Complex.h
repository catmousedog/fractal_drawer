#pragma once

#include "Vector.h"
#include "Util.h"

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

	inline Complex operator+(const Complex& v) const
	{
		return Complex(v.x + x, v.y + y);
	}

	inline Complex operator-(const Complex& v) const
	{
		return Complex(v.x - x, v.y - y);
	}

	inline Complex operator*(const double a) const
	{
		return Complex(x * a, y * a);
	}

	inline Complex operator*(const Complex& c) const
	{
		return Complex(x * c.x - y * c.y, x * c.y + y * c.x);
	}

	inline Complex operator/(const Complex& c) const
	{
		return (*this * (~c)) * (1 / c.AbsSquared());
	}

	inline Complex operator^(const double P) const
	{
		double A = pow(AbsSquared(), P / 2);
		double theta = atan2(y, x);
		return Complex(A * cos(theta * P), A * sin(theta * P));
	}

	//Complex operator^(const int P) const
	//{
	//	if (P > 0)
	//	{
	//		Complex c(*this);
	//		for (int i = 0; i < P - 1; i++)
	//			c *= *this;
	//		return c;
	//	}
	//	else if (P == 0)
	//	{
	//		return Complex(1, 0);
	//	}
	//	else
	//	{
	//		Complex t(1, 0);
	//		for (int i = 0; i < -P; i++)
	//			t *= *this;
	//		return Complex(1, 0) / t;
	//	}
	//}

	inline Complex& operator=(const Complex& c)
	{
		x = c.x;
		y = c.y;
		return *this;
	}
	inline Complex& operator+=(const Complex& c)
	{
		x += c.x;
		y += c.y;
		return *this;
	}

	inline Complex& operator-=(const Complex& c)
	{
		x -= c.x;
		y -= c.y;
		return *this;
	}

	inline Complex& operator*=(const Complex& c)
	{
		double tx = x * c.x - y * c.y;
		this->y = x * c.y + y * c.x;
		this->x = tx;
		return *this;
		//*this = *this * c;
		//return *this;
	}

	inline Complex& operator/=(const Complex& c)
	{
		*this = *this / c;
		return *this;
	}

	inline std::string string()
	{
		return to_string(x) + ", " + to_string(y);
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
	inline Complex poly(Complex q, const int a) const
	{
		q -= *this;
		return q ^ (a * m);
	}

	inline Pole operator=(const Pole& p)
	{
		x = p.x;
		y = p.y;
		m = p.m;
		return *this;
	}
	inline Pole operator+(const Vector& v)
	{
		return Pole(x + v.x, y + v.y, m);
	}

	inline Pole& operator+=(const Vector& v)
	{
		*this = *this + v;
		return *this;
	}
	inline Pole& operator+=(const Pole& p)
	{
		x += p.x;
		y += p.y;
		m += p.m;
		return *this;
	}

	inline std::string string()
	{
		
		return to_string(x) + ", " + to_string(y) + ", " + to_string(m);
	}

};
