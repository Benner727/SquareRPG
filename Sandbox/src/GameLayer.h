#pragma once

#include <Square.h>

class GameLayer : public Square::Layer
{
public:
	GameLayer();

	~GameLayer();

private:
	Square::Text* mText;

public:
	void OnUpdate() override;
	void OnRender() override;
};