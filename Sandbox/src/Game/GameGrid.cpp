#include "GameGrid.h"

GameGrid::GameGrid(Map* map)
	: mMap(map)
{
}

GameGrid::~GameGrid()
{
}

std::vector<GridObject*> GameGrid::GetGridObjects(Point p)
{
	std::vector<GridObject*> mGridObjects;

	Cell* cell = mMap->GetCell(p);
	if (cell)
	{
		for (const auto& groundItem : cell->GetGroundItems())
		{
			for (const auto& action : groundItem->Actions())
			{
				mGridObjects.push_back(new GridObject(action, groundItem));
			}
		}

		for (const auto& command : cell->GetTile()->Commands())
			mGridObjects.push_back(new GridObject(command, cell->GetTile()));
	}

	return mGridObjects;
}