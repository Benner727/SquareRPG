#include "GameLayer.h"


GameLayer::GameLayer() :
	mInterface(mPlayer), mItemFactory(ItemFactory::Instance())
{
	Item* mItem1 = mItemFactory.GetItem(2, 1);
	Item* mItem2 = mItemFactory.GetItem(2, 1);
	mPlayer.Inventory().Add(mItem1);
	mPlayer.Inventory().Add(mItem2);
}


void GameLayer::OnUpdate()
{
	mInterface.HandleInput();
}

void GameLayer::OnRender()
{
	mInterface.Render();
}