#include "Region.h"

Region::Region(int topLeftX, int topLeftY, std::map<int, std::vector<Tile*>> layers)
	: mTopLeftX(topLeftX), mTopLeftY(topLeftY), mLayers(layers)
{
	int x = 0;
	int y = 0;

	for (auto layer : mLayers)
	{
		for (auto tile : layer.second)
		{
			tile->Pos(Square::Vector2(x + mTopLeftX, y + mTopLeftY) * 32 + 16);
			
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
	std::cout << "hi" << std::endl;
	for (auto layer : mLayers)
	{
		for (auto tile : layer.second)
		{
			delete tile;
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
