
#pragma once

#include <string>

struct Vector
{
	double x, y;

	Vector() : x(0), y(0)
	{
	}
	Vector(double x, double y) : x(x), y(y)
	{
	}
	Vector(const Vector& v) : x(v.x), y(v.y)
	{
	}

	bool IsZero() const
	{
		return x == 0 && y == 0;
	}
	double AbsSquared() const
	{
		return x * x + y * y;
	}
	Vector operator-() const
	{
		return Vector(-x, -y);
	}
	Vector operator+(const Vector v) const
	{
		return Vector(v.x + x, v.y + y);
	}
	Vector operator-(const Vector v) const
	{
		return Vector(v.x - x, v.y - y);
	}
	double operator*(const Vector v) const
	{
		return v.x * x + v.y * y;
	}
	Vector operator*(const double a) const
	{
		return Vector(x * a, y * a);
	}
	Vector& operator+=(const Vector v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	std::string string()
	{
		return "v: " + std::to_string(x) + " | " + std::to_string(y);
	}
};

inline int sgn(double v)
{
	return (v > 0) - (v < 0);
}
inline Vector sgn(Vector v)
{
	return Vector(sgn(v.x), sgn(v.y));
}