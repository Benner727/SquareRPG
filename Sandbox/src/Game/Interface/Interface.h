#pragma once

#include <Square.h>

#include "Game/Player/Player.h"
#include "MenuContainer.h"
#include "InventoryContainer.h"

class Interface : public Square::GameObject
{
private:
	Player& mPlayer;
	MenuContainer mMenu;
	InventoryContainer mInventory;

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

