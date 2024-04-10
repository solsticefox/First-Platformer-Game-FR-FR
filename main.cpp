#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <vector>
#include "Utils.hpp"
#include "Map.hpp"
#include <fstream>


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
	SDL_Texture* skyTexture = window.loadTexture("Assets/sky.png");

	//Render map here
	Map lvl1("Assets/lvlmap.txt");
	lvl1.addTerrain(skyTexture);
	lvl1.addTerrain(grassTexture);
	lvl1.addTerrain(dirtTexture);
	lvl1.addTerrain(platformTexture);

	
	Entity billy(Vector2f(5, 5), playerTexture, 64, 96);

	


	bool gameRunning = true;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	SDL_Event event;
	int yvelocity = 0;
	int xvelocity = 0;
	int gravity = 1;
	Uint32 aniTick = 0;

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
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
						yvelocity = 25;
						break;
					case SDLK_s:
						yvelocity = -10;
						break;
					case SDLK_d:
						xvelocity = 10;
						break;
					case SDLK_a:
						xvelocity = -10;
						break;
					case SDLK_q:
						gameRunning = false;
						break;
					default:
						break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					case SDLK_w:
						yvelocity = 0;
						break;
					case SDLK_s:
						yvelocity = 0;
						break;
					case SDLK_d:
						xvelocity = 0;
						break;		
					case SDLK_a:
						xvelocity = 0;
						break;
					default:
						break;
					}
					break;
				}
			}
			accumulator -= timeStep;

		}

		const float alpha = accumulator / timeStep;
		billy.getPos().yvec -= yvelocity;
		billy.getPos().xvec += xvelocity;
		if (billy.getPos().yvec > 600)
		{
			billy.getPos().yvec = 600;
		}
		if (billy.getPos().yvec < 600)
		{
			yvelocity -= gravity;
		}
		if (billy.getPos().yvec == 600)
		{
			yvelocity = 0;
		}
		if (billy.getPos().yvec < 0)
		{
			billy.getPos().yvec = 0;
		}
		if (billy.getPos().xvec < 0) {
			billy.getPos().xvec = 0;
		}
		if (billy.getPos().xvec > 1280)
		{
			billy.getPos().xvec = 1280;
		}
		if (billy.getCurrentFrame().x == 0&&(SDL_GetTicks()-aniTick)>1000)
		{
			billy.setCurrentFrame(64, 0);
			aniTick = SDL_GetTicks();
		}
		else if(billy.getCurrentFrame().x == 64&& (SDL_GetTicks() - aniTick) > 1000)
		{
			billy.setCurrentFrame(0, 0);
			aniTick = SDL_GetTicks();
		}

		window.clear();

		lvl1.renderMap(window.getRenderer());
		window.render(billy);

		window.display();

		int frameTicks = SDL_GetTicks() - startTick;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
		
	}

	window.cleanup();
	SDL_Quit();

	return 0;
}