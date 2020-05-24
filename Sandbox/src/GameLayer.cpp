#include "GameLayer.h"

GameLayer::GameLayer()
{
	mPlayer = std::make_shared<Player>();

	for (int i = 1; i < 10; i++)
	{
		mPlayer->Inventory().Add(ItemFactory::Instance().GetItem(i));
	}

	mPlayer->MapPosition(Point(6, 2, 0));

	mMap = std::make_shared<Map>();

	mPlayerUI = new PlayerInterface(mPlayer, mMap, mNpcHandler);

	std::shared_ptr<NpcController> npc = std::make_shared<NpcController>(1, Point(3, 3), mMap, mPlayer);
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
	
	mNpcHandler.RenderNPC();
	mPlayer->Render();
	mNpcHandler.RenderCombatUI();

	mPlayerUI->Render();
}