#pragma once

#include <Square.h>

#include "Game/Interface/PlayerInterface.h"
#include "Game/Items/ItemFactory.h"
#include "Game/World/Map/Map.h"
#include "Game/World/Map/PathFinder.h"
#include "Game/World/Npc/NpcController.h"
#include "Game/World/Player/PlayerFactory.h"

class GameLayer : public Square::Layer
{
private:
	PlayerFactory mPlayerFactory;
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<PlayerInterface> mPlayerUI;
	std::shared_ptr<MessageLog> mMessageLog;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<NpcHandler> mNpcHandler;

public:

	GameLayer();
	virtual ~GameLayer();

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};