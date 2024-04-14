#pragma once
#include "math.h"
class BOX
{
public:
	int top, bottom, right, left;
	BOX(int Top, int Bottom, int Right, int Left)
		:top(Top), bottom(Bottom), right(Right), left(Left) {}

};

class Velocity
{
public:
	Vector2f velocity;
	Velocity(float x, float y)
	{
		velocity.xvec = x;
		velocity.yvec = y;
	}
};