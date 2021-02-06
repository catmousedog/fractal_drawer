#pragma once

#include "Complex.h"

struct Pole : Complex
{
	float m;

	//evaluates a complex number in the polynomial belonging to this pole
	inline Complex poly(const Complex q) const
	{
		return (q - *this) ^ m;
	}
	Pole() : m(0)
	{
	}
	Pole(float X, float Y, float M) : Complex(X, Y), m(M)
	{
	}
	//copy contstructor
	Pole(const Pole& p) : Complex(p), m(p.m)
	{
	}
	inline std::string string()
	{
		return "p: " + std::to_string(x) + " | " + std::to_string(y) + " | " = std::to_string(m);
	}
};
