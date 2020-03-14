#include "GameLayer.h"

GameLayer::GameLayer() :
	mInterface(mPlayer), mItemFactory(ItemFactory::Instance())
{
	Item* mItem1 = mItemFactory.GetItem(2, 1);
	Item* mItem2 = mItemFactory.GetItem(4, 1);
	mPlayer.Inventory().Add(mItem1);
	mPlayer.Inventory().Add(mItem2);

	tooltip = new Tooltip("hello BOOGABOOGA", 15, { 255,255,255,255 });
	tooltip->Parent(nullptr);
	tooltip->Pos(Square::Vector2(200, 200));
}

GameLayer::~GameLayer()
{
}


void GameLayer::OnUpdate()
{
	mInterface.HandleInput();
}

void GameLayer::OnRender()
{
	mInterface.Render();
	tooltip->Render();
}