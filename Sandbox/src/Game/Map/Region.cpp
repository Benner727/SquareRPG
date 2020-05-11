#include "Region.h"

Region::Region(int topLeftX, int topLeftY, std::map<int, std::vector<Cell*>> layers)
	: mTopLeftX(topLeftX), mTopLeftY(topLeftY), mLayers(layers)
{
	int x = 0;
	int y = 0;

	for (auto layer : mLayers)
	{
		for (auto cell : layer.second)
		{
			cell->Pos(Square::Vector2(x + mTopLeftX, y + mTopLeftY) * 32 + 16);
			
			x++;
			if (x == SIZE)
			{
				x = 0;
				y++;
			}
		}
	}
}

Region::~Region()
{
	for (auto layer : mLayers)
	{
		for (auto cell : layer.second)
		{
			delete cell;
		}
	}
}

bool Region::Contains(Point p)
{
	return (
		p.x >= mTopLeftX && p.x < mTopLeftX + SIZE &&
		p.y >= mTopLeftY && p.y < mTopLeftY + SIZE
	);
}
