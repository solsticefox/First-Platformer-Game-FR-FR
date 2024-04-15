#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include <vector>
#include "Utils.hpp"
#include "Map.hpp"
#include <fstream>

#define UNIT 32

void createBlock(float x, float y, std::vector<Entity>& blocks, SDL_Texture* tex)
{
	Entity blockT(Vector2f(x, y), tex);
	blockT.addBox();
	blocks.push_back(blockT);
}

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

	std::vector<Entity> blocks;

	createBlock(6*UNIT, 16*UNIT, blocks, platformTexture);

	createBlock(7*UNIT, 16*UNIT, blocks, platformTexture);

	createBlock(8*UNIT, 16*UNIT, blocks, platformTexture);

	createBlock(12 * UNIT, 10 * UNIT, blocks, platformTexture);

	createBlock(13 * UNIT, 10 * UNIT, blocks, platformTexture);

	createBlock(14 * UNIT, 10 * UNIT, blocks, platformTexture);

	createBlock(18 * UNIT, 13 * UNIT, blocks, platformTexture);

	createBlock(19 * UNIT, 13 * UNIT, blocks, platformTexture);

	createBlock(20 * UNIT, 13 * UNIT, blocks, platformTexture);

	createBlock(23 * UNIT, 18 * UNIT, blocks, platformTexture);

	createBlock(24 * UNIT, 18 * UNIT, blocks, platformTexture);

	createBlock(25 * UNIT, 18 * UNIT, blocks, platformTexture);

	createBlock(30 * UNIT, 8 * UNIT, blocks, platformTexture);

	createBlock(31 * UNIT, 8 * UNIT, blocks, platformTexture);

	createBlock(32 * UNIT, 8 * UNIT, blocks, platformTexture);

	Entity billy(Vector2f(5, 5), playerTexture, 64, 96);
	billy.addVelocity();
	billy.addBox();


	bool gameRunning = true;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	SDL_Event event;
	int gravity = 1;
	Uint32 aniTick = 0;

	int collider;

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
						billy.entVel->velocity.yvec = 25;
						break;
					case SDLK_s:
						billy.entVel->velocity.yvec = -10;
						break;
					case SDLK_d:
						billy.entVel->velocity.xvec = 3;
						break;
					case SDLK_a:
						billy.entVel->velocity.xvec = -3;
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
						billy.entVel->velocity.yvec = 0;
						break;
					case SDLK_s:
						billy.entVel->velocity.yvec = 0;
						break;
					case SDLK_d:
						billy.entVel->velocity.xvec = 0;
						break;		
					case SDLK_a:
						billy.entVel->velocity.xvec = 0;
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
		billy.setEntBox();
		billy.getPos().yvec -= billy.entVel->velocity.yvec;
		billy.getPos().xvec += billy.entVel->velocity.xvec;
		for (auto& block : blocks)
		{
			block.setEntBox();
		}

		for (auto& block : blocks)
		{
			collider = billy.entBox->checkCollision(*billy.entBox, *block.entBox);
			switch (collider)
			{
			case 1:
				billy.entVel->velocity.xvec = 0;
				billy.getPos().xvec = block.getPos().xvec - billy.getCurrentFrame().w;
				break;
			case 2:
				billy.entVel->velocity.xvec = 0;
				billy.getPos().xvec = block.getPos().xvec + block.getCurrentFrame().w;
				break;
			case 3:
				gravity = 0;
				billy.entVel->velocity.yvec = 0;
				billy.getPos().yvec = block.getPos().yvec + block.getCurrentFrame().h;
				break;
			case 4:
				gravity = 0;
				billy.entVel->velocity.yvec = 0;
				billy.getPos().yvec = block.getPos().yvec - billy.getCurrentFrame().h-5;
				break;
			default:
				gravity = 1;
				break;
			}
		}

		if (billy.getPos().yvec > 600)
		{
			billy.getPos().yvec = 600;
		}
		if (billy.getPos().yvec < 600)
		{
			billy.entVel->velocity.yvec -= gravity;
		}
		if (billy.getPos().yvec == 600)
		{
			billy.entVel->velocity.yvec = 0;
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
		for (auto& block : blocks)
		{
			window.render(block);
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