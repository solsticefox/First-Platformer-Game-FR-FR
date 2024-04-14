#pragma once
#include "Entity.hpp"
#include <map>
#include <vector>
#include "Components.hpp"

class ComponentManager
{
public:
    std::map<int, ScreenPosition*> positions;
    void addPositionComponent(int entID, int x, int y);

    std::map<int, hasTexture*> textures;
    void addTextureComponent(int entID, const char* filename);

    std::map<int, Rectangle*> rectangles;
    void addRectangle(int entID, int width, int height);
};

//Declare renderer as well as component manager
class EntityManager
{
public:
    static ComponentManager* cManager;
    static SDL_Renderer* ren;
    std::vector<int> entities;
    void addToEntities(int eid);
    void RenderEntity(int EntID);

};