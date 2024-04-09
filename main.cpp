#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.hpp"
#include "Entity.hpp"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init has FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "IMG_init has FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	RenderWindow window("Game v1.0", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("Assets/ground_grass_1.png");

	Entity platform0(10, 10, grassTexture);



	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
		}

		window.clear();
		window.render(platform0);
		window.display();
	}

	window.cleanup();
	SDL_Quit();

	return 0;
}