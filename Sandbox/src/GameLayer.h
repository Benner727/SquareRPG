#pragma once

#include <Square.h>

#include "Game/Interface/PlayerInterface.h"
#include "Game/Items/ItemFactory.h"
#include "Game/World/Map/Map.h"
#include "Game/World/Map/PathFinder.h"
#include "Game/World/Npc/NpcController.h"

class GameLayer : public Square::Layer
{
private:
	std::shared_ptr<Player> mPlayer;
	PlayerInterface* mPlayerUI;
	std::shared_ptr<Map> mMap;
	NpcHandler mNpcHandler;

public:

	GameLayer();
	virtual ~GameLayer();

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};