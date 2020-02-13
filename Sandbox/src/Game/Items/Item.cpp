#include "Game/Items/Item.h"

Item::Item(int index, int amount)
{
	mIndex = index;
	mAmount = amount;

	mSprite = nullptr;
	mItemDefinition = nullptr;
}

Item::~Item()
{
	delete mSprite;
}

void Item::Render()
{
	mSprite->Render();
}
