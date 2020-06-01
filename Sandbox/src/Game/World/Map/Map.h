#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "Game/World/Map/Region.h"
#include "Game/Point.h"


class Map
{
private:
	const int TILE_SIZE = 16;
	const int TILESET_WIDTH = 192;

	int mWidth;
	int mHeight;

	std::vector<Region*> mRegions;

	void LoadTileset();
	void LoadRegions();

public:
	Map();
	~Map();

	int Width() const { return mWidth; }
	int Height() const { return mHeight; }

	Cell* GetCell(Point p) const;
	std::vector<std::string> TileCommands(Point p);
	bool TileWalkable (Point p) const;
	bool TileCanAttackOver (Point p) const;

	void Update(int z);
	void Render(int z);
};