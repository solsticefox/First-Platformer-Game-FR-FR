#include "Components.hpp"

hasTexture::hasTexture(const char* filename)
{
	loadNewTex(filename);
}

void hasTexture::loadNewTex(const char* p_filepath)
{
	tex = window.loadTexture(p_filepath);
}

Rectangle::Rectangle(int width, int height)
{
	srcrect.w = width;
	srcrect.h = height;
	srcrect.x = 0;
	srcrect.y = 0;
	dstrect.w = width;
	dstrect.h = height;
}