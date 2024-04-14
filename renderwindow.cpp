#include "RenderWindow.hpp"
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "Entity.hpp"

#define UNIT 32

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_RESIZABLE);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}

void RenderWindow::cleanup()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}



void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}