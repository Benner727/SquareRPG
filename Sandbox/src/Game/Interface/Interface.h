#pragma once

#include <Square.h>

#include "Game/Player/Player.h"
#include "Menu.h"

class Interface : public Square::GameObject
{
private:
	Player mPlayer;
	Menu mMenu;

	Square::InputHandler& mInputHandler;
	//std::vector<Square::Sprite> mBackgroundSprites;

	void InitializeBackground();

public:
	Interface(Player player = Player());
	~Interface();

	void HandleInput();
	void Render();
};

