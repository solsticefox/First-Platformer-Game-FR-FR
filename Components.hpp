#pragma once
#include "math.h"
#include <iostream>
class BOX
{
public:
	int top, bottom, right, left;
	BOX(int Top, int Bottom, int Right, int Left)
		:top(Top), bottom(Bottom), right(Right), left(Left) {}
	void updateBox(int t, int b, int r, int l)
	{
		top = t;
		bottom = b;
		right = r;
		left = l;
	}

	
	bool checkCollision(BOX box1, BOX box2)
	{
		bool check = false;

		if (box1.bottom<box2.bottom&&box1.bottom>box2.top&&box1.right<box2.right)
			check = true;
		return check;
	}

	void printBox()
	{
		std::cout << "Box coordinates are: " << "horizontal: " << right << ", " << left << " vertical: " << top << ", " << bottom << std::endl;
	}

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