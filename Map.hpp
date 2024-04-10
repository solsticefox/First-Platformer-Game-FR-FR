#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>

class Map {
public:
	Map(const char* filename);
	~Map();
	void loadMap(const char* filename);
	void renderMap(SDL_Renderer* ren);
	void addTerrain(SDL_Texture* tex);
private:
	std::vector<std::vector<int>> mapArr;
	std::vector<SDL_Texture*> terrain;
	int numRows;
	int numColumns;
};