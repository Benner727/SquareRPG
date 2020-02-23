#include "GameLayer.h"

#include "Game/Interface/Interface.h"
#include "Game/Player/Player.h"

GameLayer::GameLayer() :
	mPlayer(Player()), mInterface(Interface(mPlayer))
{

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
}