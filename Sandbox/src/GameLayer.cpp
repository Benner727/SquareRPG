#include "GameLayer.h"

GameLayer::GameLayer()
{
	mMessageLog = std::make_shared<MessageLog>(50, 8, "Font/VeraMono.ttf", 14, Square::Vector2(15.0f, -15.0f));
	mMap = std::make_shared<Map>();
	mNpcHandler = std::make_shared<NpcHandler>();

	mPlayer = mPlayerFactory.NewPlayer(mPlayerUI, mMap, mMessageLog, mNpcHandler);

	std::shared_ptr<NpcController> npc = std::make_shared<NpcController>(1, Point(3, 3), mMap, mPlayer);
	mNpcHandler->AddNpc(npc);
}

GameLayer::~GameLayer()
{

}

void GameLayer::OnUpdate()
{
	mMap->Update(mPlayer->MapPosition().z);
	mNpcHandler->Update();
	mPlayer->Update();
	mPlayerUI->Update();
}

void GameLayer::OnRender()
{
	mMap->Render(mPlayer->MapPosition().z);
	
	mNpcHandler->RenderNPC();
	mPlayer->Render();
	mNpcHandler->RenderCombatUI();

	mPlayerUI->Render();
}