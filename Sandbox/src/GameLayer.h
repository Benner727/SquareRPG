#pragma once

#include <Square.h>

#include "Game/Interface/PlayerInterface.h"
#include "Game/Items/ItemFactory.h"

class GameLayer : public Square::Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	Player* player;
	PlayerInterface* playerUI;

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};