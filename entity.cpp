#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

#define UNIT 32

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int width, int height)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = width;
	currentFrame.h = height;
}



SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
