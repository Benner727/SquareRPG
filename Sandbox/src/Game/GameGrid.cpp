#include "GameGrid.h"

GameGrid::GameGrid(std::shared_ptr<Map> map)
	: mMap(map)
{
}

GameGrid::~GameGrid()
{
}

std::vector<std::shared_ptr<GridObject>> GameGrid::GetGridObjects(Point p)
{
	std::vector<std::shared_ptr<GridObject>> mGridObjects;

	Cell* cell = mMap->GetCell(p);
	if (cell)
	{
		for (const auto& groundItem : cell->GetGroundItems())
		{
			for (const auto& action : groundItem->Actions())
			{
				mGridObjects.push_back(std::make_shared<GridObject>(action, groundItem));
			}
		}

		for (const auto& command : cell->GetTile()->Commands())
			mGridObjects.push_back(std::make_shared<GridObject>(command, cell->GetTile()));
	}

	return mGridObjects;
}