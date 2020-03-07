#pragma once

#include <vector>
#include <string>

#include "Game/Map/Tile.h"
#include "Game/Point.h"


class Map
{
private:
	int width;
	int height;

	std::vector<Tile> mTiles;


public:
	std::vector<std::string> TileCommands(Point p) {};

	void Update();
	void Render();

};