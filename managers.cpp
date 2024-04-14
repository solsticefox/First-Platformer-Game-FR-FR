#include "Managers.hpp"
#include "Components.hpp"
#include <vector>

void ComponentManager::addPositionComponent(int entID, int x, int y)
{
    positions[entID] = new ScreenPosition(x, y);
};

void ComponentManager::addTextureComponent(int entID, const char* filename)
{
    textures[entID] = new hasTexture(filename);
};

void ComponentManager::addRectangle(int entID, int width, int height)
{
    rectangles[entID] = new Rectangle(width, height);
};

void EntityManager::addToEntities(int eid)
{
    entities.push_back(eid);
}

void EntityManager::RenderEntity(int EntID)
{
    SDL_RenderCopy(ren, cManager->textures[EntID]->tex, &cManager[EntID]->rectangles->srcrect, &cManager[EntID]->rectangles->dstrect);
}