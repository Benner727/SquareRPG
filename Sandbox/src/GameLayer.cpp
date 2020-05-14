#include "GameLayer.h"
#include "Game//Npc/NpcFactory.h"
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

	{
		std::shared_ptr<Npc> npc = NpcFactory::Instance().GetNpc(1);
	}

	mPlayerUI = new PlayerInterface(mPlayer, mMap);
}

GameLayer::~GameLayer()
{
	delete mPlayerUI;
}

void GameLayer::OnUpdate()
{
	mMap->Update(0);
	mPlayer->Update();
	mPlayerUI->Update();
}

void GameLayer::OnRender()
{
	mMap->Render(0);
	mPlayer->Render();
	mPlayerUI->Render();
}