#include "Cell.h"

Cell::Cell(Tile* tile, std::vector<GroundItem*> groundItems)
	: mTile(tile), mGroundItems(groundItems)
{
	mTile->Parent(this);
	
	for (auto groundItem : mGroundItems)
		groundItem->Parent(this);
}

Cell::~Cell()
{
	delete mTile;

	for (auto groundItem : mGroundItems)
		delete groundItem;
}

void Cell::AddGroundItem(Item* item)
{ 
	mGroundItems.insert(mGroundItems.begin(), new GroundItem(item));
	mGroundItems.front()->Parent(this);
	mGroundItems.front()->Pos(Square::VEC2_ZERO);
}

void Cell::Update()
{
	mTile->Update();

	for (std::vector<GroundItem*>::iterator it = mGroundItems.begin(); it != mGroundItems.end();)
	{
		if ((*it)->Expired())
		{
			delete* it;
			it = mGroundItems.erase(it);
		}
		else
		{
			(*it)->Update();
			++it;
		}
	}
}

void Cell::Render()
{
	mTile->Render();

	for (auto groundItem : mGroundItems)
		groundItem->Render();
}
