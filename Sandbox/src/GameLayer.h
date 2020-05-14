#pragma once

#include <Square.h>

#include "Game/Interface/PlayerInterface.h"
#include "Game/Items/ItemFactory.h"
#include "Game/Map/Map.h"
#include "Game/Map/PathFinder.h"
#include "Game/Player/Player.h"

class GameLayer : public Square::Layer
{
private:
	std::shared_ptr<Player> mPlayer;
	PlayerInterface* mPlayerUI;
	std::shared_ptr<Map> mMap;

public:

	GameLayer();
	virtual ~GameLayer();

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};