#pragma once

#include <Square.h>

#include "Game/Interface/PlayerInterface.h"
#include "Game/Items/ItemFactory.h"
#include "Game/Map/Map.h"
#include "Game/Map/PathFinder.h"
#include "Game/Player/Player.h"

class GameLayer : public Square::Layer
{
public:
	Map map;
	Player player;
	
	void HandlePathing();

	GameLayer();
	virtual ~GameLayer();

	Player* player;
	PlayerInterface* playerUI;

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};