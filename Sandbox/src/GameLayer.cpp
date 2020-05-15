#include "GameLayer.h"

GameLayer::GameLayer()
{
	mPlayer = std::make_shared<Player>();

	for (int i = 0; i < 10; i++)
	{
		mPlayer->Inventory().Add(ItemFactory::Instance().GetItem(2));
		mPlayer->Inventory().Add(ItemFactory::Instance().GetItem(4));
	}

	mPlayer->Inventory().Remove(2);
	mPlayer->Inventory().Remove(7);
	mPlayer->Inventory().Remove(17);

	mMap = std::make_shared<Map>();

	mPlayerUI = new PlayerInterface(mPlayer, mMap);
}

GameLayer::~GameLayer()
{
	delete mPlayerUI;
}

void GameLayer::OnUpdate()
{
	mMap->Update(mPlayer->MapPosition().z);
	mPlayer->Update();
	mPlayerUI->Update();
}

void GameLayer::OnRender()
{
	mMap->Render(mPlayer->MapPosition().z);
	mPlayer->Render();
	mPlayerUI->Render();
}