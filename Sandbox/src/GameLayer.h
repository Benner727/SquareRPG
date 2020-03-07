#pragma once

#include <Square.h>

class GameLayer : public Square::Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void OnUpdate() override;
	virtual void OnRender() override;
};