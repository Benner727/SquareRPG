#pragma once

#include <Square.h>

#include "Game/Player/Player.h";
#include "Game/Interface/Interface.h";

class GameLayer : public Square::Layer
{
private:
	Player mPlayer;
	Interface mInterface;

public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};