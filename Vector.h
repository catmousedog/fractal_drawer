
#pragma once

#include <string>

struct Vector
{
	float x, y;

	Vector() : x(0), y(0)
	{
	}
	Vector(float x, float y) : x(x), y(y)
	{
	}
	Vector(const Vector& v) : x(v.x), y(v.y)
	{
	}

	bool IsZero() const
	{
		return x == 0 && y == 0;
	}
	float AbsSquared() const
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
	float operator*(const Vector v) const
	{
		return v.x * x + v.y * y;
	}
	Vector operator*(const float a) const
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