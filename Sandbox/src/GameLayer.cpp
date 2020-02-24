#include "GameLayer.h"

#include "Game/Interface/Interface.h"
#include "Game/Player/Player.h"

GameLayer::GameLayer() :
	mInterface(mPlayer)
{
	
}


void GameLayer::OnUpdate()
{
	mInterface.HandleInput();
}

void GameLayer::OnRender()
{
	mInterface.Render();
}