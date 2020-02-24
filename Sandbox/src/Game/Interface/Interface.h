#pragma once

#include <Square.h>

#include "Game/Player/Player.h"
#include "Menu.h"
#include "InventoryInterface.h"

class Interface : public Square::GameObject
{
private:
	Player& mPlayer;
	Menu mMenu;
	InventoryInterface mInventory;

	int mActiveMenu = -1;

	Square::InputHandler& mInputHandler;
	//std::vector<Square::Sprite> mBackgroundSprites;

	void InitializeBackground();

public:
	Interface(Player& player);
	~Interface();

	void HandleInput();
	void Render();
};

