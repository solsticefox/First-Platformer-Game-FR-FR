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

	
	int checkCollision(BOX box1, BOX box2)
	{
		int check = 0;
		int bHor = (box1.bottom + box1.top) / 2;
		int bVer = (box1.left + box1.right) / 2;
		if (bHor<box2.bottom&&bHor>box2.top&&box1.right<box2.right&&box1.right>box2.left)
			check = 1; //Right edge collision
		if (bHor<box2.bottom && bHor>box2.top && box1.left<box2.right && box1.left>box2.left)
			check = 2; //Left edge collision
		if (bVer > box2.left && bVer < box2.right && box1.top<box2.bottom && box1.bottom>box2.bottom)
			check = 3; //Top edge collision
		if (bVer > box2.left && bVer < box2.right && box1.bottom>box2.top && box1.bottom < box2.bottom)
			check = 4;	//Bottom edge collision


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