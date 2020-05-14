#include "Cell.h"

Cell::Cell(std::shared_ptr<Tile*> tile, std::vector<Item*> groundItems)
	: mTile(tile)
{
	(*mTile)->Parent(this);
	
	for (auto groundItem : groundItems)
		AddGroundItem(groundItem);
}

Cell::~Cell()
{
}

void Cell::AddGroundItem(Item* item)
{ 
	mGroundItems.insert(mGroundItems.begin(), std::make_shared<GroundItem*>(new GroundItem(item)));
	(*mGroundItems.front())->Parent(this);
	(*mGroundItems.front())->Pos(Square::VEC2_ZERO);
}

void Cell::Update()
{
	(*mTile)->Update();

	for (std::vector<std::shared_ptr<GroundItem*>>::iterator it = mGroundItems.begin(); it != mGroundItems.end();)
	{
		if ((**it)->Expired())
		{
			it = mGroundItems.erase(it);
		}
		else
		{
			(**it)->Update();
			++it;
		}
	}
}

void Cell::Render()
{
	(*mTile)->Render();

	for (auto groundItem : mGroundItems)
		(*groundItem)->Render();
}
