#include "Map.hpp"

Map::~Map() {}

Map::Map(const char* filename)
{
	loadMap(filename);
}

void Map::loadMap(const char* filename)
{
	std::ifstream file(filename);

	mapArr.push_back(std::vector<int>());
	int j = 0;
	int cint;
	char cchar;

	while (file) {
		cchar = file.get();
		if (cchar != 10)
		{
			cint = cchar - '0';
			mapArr[j].push_back(cint);
		}
		else
		{
			mapArr.push_back(std::vector<int>());
			j++;
		}
	}
	numRows = j;
	numColumns = mapArr[0].size();
	file.close();
}


void Map::addTerrain(SDL_Texture* tex) {
	terrain.push_back(tex);
	std::cout << terrain.size() << std::endl;
}

void Map::renderMap(SDL_Renderer* ren)
{
	SDL_Rect msrc;
	msrc.x = 0;
	msrc.y = 0;
	msrc.w = 32;
	msrc.h = 32;
	SDL_Rect mdst;
	mdst.w = 32;
	mdst.h = 32;
	SDL_Texture* cTex = IMG_LoadTexture(ren, "Assets/grass.png");
	for (int x = 0; x < numColumns; x++)
	{
		for (int y = 0; y < numRows; y++)
		{
			cTex = terrain[mapArr[y][x]];
			mdst.x = x * 32;
			mdst.y = y * 32;
			SDL_RenderCopy(ren, cTex, &msrc, &mdst);
		}
	}
}