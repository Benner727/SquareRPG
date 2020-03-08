#pragma once

#include <vector>
#include <map>

#include "Game/Map/Tile.h"
#include "Game/Point.h"

class Region
{
public:
	static const int SIZE = 256;

private:
	int mTopLeftX;
	int mTopLeftY;

	std::map<int, std::vector<Tile*>> mLayers;
	
public:
	Region(int topLeftX, int topLeftY, std::map<int, std::vector<Tile*>> tiles);
	~Region();

	inline int TopLeftX() const { return mTopLeftX; }
	inline int TopLeftY() const { return mTopLeftY; }
	inline std::vector<Tile*> Tiles(int depth) { return mLayers[depth]; }

	bool Contains(Point p);
};
