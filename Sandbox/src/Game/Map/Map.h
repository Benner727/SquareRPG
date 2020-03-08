#pragma once

#include <vector>
#include <string>

#include "Game/Map/Region.h"
#include "Game/Point.h"


class Map
{
private:
	int mWidth;
	int mHeight;

	std::vector<Region*> mRegions;

public:
	Map();
	~Map();

	Tile* GetTile(Point p);
	std::vector<std::string> TileCommands(Point p);
	bool TileWalkable(Point p);
	bool TileCanAttackOver(Point p);

	void Update(int z);
	void Render(int z);

};