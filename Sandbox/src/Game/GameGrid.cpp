#include "GameGrid.h"

GameGrid::GameGrid(Map& map)
	: mMap(map)
{
}

GameGrid::~GameGrid()
{
}

std::vector<GridObject*> GameGrid::GetGridObjects(Point p)
{
	std::vector<GridObject*> mGridObjects;

	Tile* tile = mMap.GetTile(p);
	if (tile)
	{
		for (const auto& command : tile->Commands())
			mGridObjects.push_back(new GridObject(command, tile));
	}

	return mGridObjects;
}