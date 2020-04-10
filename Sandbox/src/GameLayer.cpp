#include "GameLayer.h"

GameLayer::GameLayer()
{
	player = new Player();

	for (int i = 0; i < 10; i++)
	{
		player->Inventory().Add(ItemFactory::Instance().GetItem(2));
		player->Inventory().Add(ItemFactory::Instance().GetItem(4));
	}

	player->Inventory().Remove(2);
	player->Inventory().Remove(7);
	player->Inventory().Remove(17);

	playerUI = new PlayerInterface(*player);
}

GameLayer::~GameLayer()
{
	delete player;
	delete playerUI;
}

void GameLayer::OnUpdate()
{
	player->Update();
	playerUI->Update();
}

void GameLayer::OnRender()
{
	playerUI->Render();
}