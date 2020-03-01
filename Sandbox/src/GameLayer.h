#pragma once

#include <Square.h>

#include "Game/Player/Player.h";
#include "Game/Interface/Interface.h";
#include "Game/Items/ItemFactory.h"

class GameLayer : public Square::Layer
{
private:
	Player mPlayer;
	Interface mInterface;
	ItemFactory& mItemFactory;

public:
	GameLayer();
	virtual ~GameLayer();

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};