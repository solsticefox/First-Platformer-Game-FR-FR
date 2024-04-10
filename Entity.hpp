#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"

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
	

private:
	Vector2f pos;
	SDL_Rect currentFrame;
	SDL_Texture* tex;

};
