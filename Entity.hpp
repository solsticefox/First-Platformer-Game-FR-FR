#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"
#include "Managers.hpp"

#define UNIT 32

//Declare the manager
class Entity
{
private:
	static int nextid;
	static EntityManager emanager;
public:
	Entity() : ENTID(nextid++) {
		emanager.addToEntities(ENTID);
	}
	int ENTID;
};

int Entity::nextid = 0;
