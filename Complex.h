#pragma once

#include <string>

struct Complex
{
	float x, y;

	Complex operator-() const
	{
		return Complex(-x, -y);
	}
	Complex operator~() const
	{
		return Complex(x, -y);
	}
	//squared abs value
	float AbsSquared() const
	{
		return x * x + y * y;
	}
	Complex operator+(const Complex c) const
	{
		return Complex(x + c.x, y + c.y);
	}
	Complex operator-(const Complex c) const
	{
		return *this + (-c);
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
	Complex() : x(0), y(0)
	{
	}
	Complex(float X, float Y) : x(X), y(Y)
	{
	}
	// copy constructor;
	Complex(const Complex& c)
	{
		x = c.x;
		y = c.y;
	}
	std::string string()
	{
		return "c: " + std::to_string(x) + " | " + std::to_string(y);
	}
};

