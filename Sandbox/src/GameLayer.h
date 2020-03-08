#pragma once

#include <Square.h>

#include "Game/Interface/PlayerInterface.h"
#include "Game/Items/ItemFactory.h"
#include "Game/Map/Map.h"

class GameLayer : public Square::Layer
{
public:
	Map map;

	GameLayer();
	virtual ~GameLayer();

	Player* player;
	PlayerInterface* playerUI;

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};