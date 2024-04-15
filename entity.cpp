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

void Entity::setCurrentFrame(int x, int y)
{
	currentFrame.x = x;
	currentFrame.y = y;
}

void Entity::addBox(int t, int b, int r, int l)
{
	entBox = new BOX(t, b, r, l);
}

void Entity::addVelocity()
{
	entVel = new Velocity(0, 0);
}

void Entity::setEntBox()
{
	entBox->updateBox(getPos().yvec, getPos().yvec + getCurrentFrame().h, getPos().xvec + getCurrentFrame().w, getPos().xvec);
}