#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <vector>

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


	std::vector<Entity> entities = { Entity(Vector2f(0, 0), grassTexture),
									  Entity(Vector2f(30, 0), grassTexture),
									  Entity(Vector2f(30,30),grassTexture) };

	{
		Entity wilson(Vector2f(100, 50), grassTexture);

		entities.push_back(wilson);
	}



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

		for (Entity& e : entities)
		{
			window.render(e);
		}

		window.display();
	}

	window.cleanup();
	SDL_Quit();

	return 0;
}