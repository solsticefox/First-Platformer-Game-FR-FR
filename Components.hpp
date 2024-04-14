#pragma once
#include "Math.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.hpp"

class ScreenPosition
{
public:
	Vector2f screenpos;
	ScreenPosition(float x, float y)
	{
		screenpos.xvec = x;
		screenpos.yvec = y;
	}
};

//initialize the render window in main
class hasTexture
{
public:
	hasTexture(const char* filename);
	static RenderWindow* win;
	SDL_Texture* tex;
	void loadNewTex(const char* p_filePath);
};

class Rectangle
{
public:
	Rectangle(int width, int height);
	SDL_Rect srcrect;
	SDL_Rect dstrect;

};
