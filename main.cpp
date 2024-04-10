#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <vector>
#include "Utils.hpp"

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

	SDL_Texture* grassTexture = window.loadTexture("Assets/grass.png");
	SDL_Texture* dirtTexture = window.loadTexture("Assets/dirt.png");
	SDL_Texture* platformTexture = window.loadTexture("Assets/platform.png");
	SDL_Texture* hitboxTexture = window.loadTexture("Assets/hitbox.png");
	SDL_Texture* playerTexture = window.loadTexture("Assets/player.png");


	std::vector<Entity> entities = { Entity(Vector2f(0, 0), grassTexture),
									  Entity(Vector2f(1, 0), hitboxTexture),
									  Entity(Vector2f(1,1),platformTexture) };

	{
		Entity billy(Vector2f(10, 50), playerTexture, 190, 96);

		entities.push_back(billy);
	}



	bool gameRunning = true;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	SDL_Event event;

	while (gameRunning)
	{
		int startTick = SDL_GetTicks();
		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;
		
		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= timeStep) {

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					gameRunning = false;
				}
			}
			accumulator -= timeStep;

		}

		const float alpha = accumulator / timeStep;

		window.clear();

		for (Entity& e : entities)
		{
			window.render(e);
		}

		window.display();

		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		
	}

	window.cleanup();
	SDL_Quit();

	return 0;
}