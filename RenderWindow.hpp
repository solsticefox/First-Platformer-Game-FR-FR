#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	~RenderWindow();


private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};