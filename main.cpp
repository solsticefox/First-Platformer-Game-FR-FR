#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <vector>
#include "Utils.hpp"
#include "Map.hpp"
#include <fstream>
#include "Components.hpp"
#include "Managers.hpp"


int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_Init has FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "IMG_init has FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	EntityManager entmanager;

	ComponentManager cmanager;


	RenderWindow window("Game v1.0", 1280, 720);

	EntityManager::ren = window.getRenderer();

	EntityManager::cManager = &cmanager;

	hasTexture::win = &window;

	/*
	SDL_Texture* grassTexture = window.loadTexture("Assets/grass.png");
	SDL_Texture* dirtTexture = window.loadTexture("Assets/dirt.png");
	SDL_Texture* platformTexture = window.loadTexture("Assets/platform.png");
	SDL_Texture* hitboxTexture = window.loadTexture("Assets/hitbox.png");
	SDL_Texture* playerTexture = window.loadTexture("Assets/player.png");
	SDL_Texture* skyTexture = window.loadTexture("Assets/sky.png");
	*/

	//Render map here
	
	/*
	Map lvl1("Assets/lvlmap.txt");
	lvl1.addTerrain(skyTexture);
	lvl1.addTerrain(grassTexture);
	lvl1.addTerrain(dirtTexture);
	lvl1.addTerrain(platformTexture);
	*/

	


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

		while (accumulator >= timeStep) 
		{

			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					gameRunning = false;
					break;
				}
			}
			accumulator -= timeStep;

		}

		const float alpha = accumulator / timeStep;

		window.clear();

		//lvl1.renderMap(window.getRenderer());

		window.display();

		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		
	}

	window.cleanup();
	SDL_Quit();

	return 0;
}