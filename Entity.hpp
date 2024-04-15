#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"
#include "Components.hpp"
#include <vector>

#define UNIT 32

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, int width = UNIT, int height = UNIT);
	Vector2f& getPos()
	{
		return pos;
	}
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void setCurrentFrame(int x, int y);
	BOX* entBox = nullptr;
	void addBox(int t = 0, int b = 0, int r = 0, int l = 0);
	Velocity* entVel = nullptr;
	void addVelocity();
	void setEntBox();

private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;

};


