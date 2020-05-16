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

	mPlayer->MapPosition(Point(2, 2, 0));

	mMap = std::make_shared<Map>();

	mPlayerUI = new PlayerInterface(mPlayer, mMap, mNpcHandler);

	std::shared_ptr<Npc> npc = NpcFactory::Instance().GetNpc(1);
	npc->MapPosition(Point(10, 7));
	mNpcHandler.AddNpc(npc);
}

GameLayer::~GameLayer()
{
	delete mPlayerUI;
}

void GameLayer::OnUpdate()
{
	mMap->Update(mPlayer->MapPosition().z);
	mNpcHandler.Update();
	mPlayer->Update();
	mPlayerUI->Update();
}

void GameLayer::OnRender()
{
	mMap->Render(mPlayer->MapPosition().z);
	mNpcHandler.Render();
	mPlayer->Render();
	mPlayerUI->Render();
}