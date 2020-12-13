#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <random>


class Fractal
{
public:
	static constexpr int m = 40, p = 200, pixels_size = p * p;
	static constexpr int thread_count = 100;

	struct Box
	{
		float x0, y0, x1, y1;
		Box(float x0, float y0, float x1, float y1) : x0(x0), y0(y0), x1(x1), y1(y1)
		{
		}
		inline float Width()
		{
			return x1 - x0;
		}
		inline float Height()
		{
			return y1 - y0;
		}
	};
	struct Complex
	{
		float x, y;

		inline Complex& operator+=(const Complex& c)
		{
			x += c.x;
			y += c.y;
			return *this;
		}
		inline Complex& operator-()
		{
			Complex c;
			c.x = -x;
			c.y = -y;
			return c;
		}
		inline Complex operator+(const Complex& c)
		{
			Complex t;
			t.x = x + c.x;
			t.y = x + c.y;
			return t;
		}

		inline Complex operator*(float a)
		{
			Complex c;
			c.x = x * a;
			c.y = x * a;
			return c;
		}
		inline Complex operator/(float a)
		{
			Complex c;
			c.x = x / a;
			c.y = x / a;
			return c;
		}
		Complex() : x(0), y(0)
		{
		}
		Complex(int X, int Y) : x(X), y(Y)
		{
		}
		Complex(const Complex& c)
		{
			x = c.x;
			y = c.y;
		}
		inline std::string string()
		{
			return std::to_string(x) + "|" + std::to_string(y);
		}
	};
	Fractal(int it, int bail, float m, float M, Box box);
	~Fractal()
	{
		delete[] coordinates;
		delete[] desired;
		delete[] pixels;
	}
	/* Functions */
	//randomize parameters
	void Randomize(int attempts, int limit);
	//the fractal function
	inline float Func(float cx, float cy) const;
	//applies the Iterator changing the pixels[] member
	void Iterate();
	//returns the cost of the current parameters
	float Cost();
	//returns the complex derivative of the 'i'th parameter
	Complex Derivative(int i, float cost);
	//does one training cycle and returns true if the Cycle was successful
	bool Cycle(bool ForceDownhill);
	//print pixels and parameters to csv files
	void Print();

	/* Getters & Setters */
	Complex* GetParameters() { return parameters; }
	inline bool InCoordinates(float x, float y);
private:

	/* Variables */
	int csteps=5;
	float dstep = 0.01f, convergent_weight = 3.0f;
	std::mt19937 rng;
	std::uniform_real_distribution<float> dist;
	std::mutex mtx;
	int iterations, bailout;
	float dx, dy;
	Box bounds;
	int relevant;
	//array of all the relevant coordinates
	Complex* coordinates;
	//array of all values in order of the relevant coordinates
	float* pixels;
	//array of all desired values in order of the relevant coordinates
	float* desired;
	Complex parameters[m];
	std::thread threads[thread_count];

	/* Functions */
	//Iterates over a portion of the total pixels
	void SubIterate(int start, int end);
};

