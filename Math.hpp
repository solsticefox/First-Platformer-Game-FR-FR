#pragma once
#include <iostream>

class Vector2f
{
public:
	Vector2f(float p_x = 0, float p_y = 0)
		:xvec(p_x), yvec(p_y)
	{}

	void print()
	{
		std::cout << xvec << ", " << yvec << std::endl;
	}

	float xvec, yvec;

};